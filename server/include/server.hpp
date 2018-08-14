#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <memory>
#include <deque>
#include <string>
#include <thread>
#include <iostream>

#ifndef __SERVER_H__
#define __SERVER_H__

using namespace boost;

template <typename ConnectionHandler>
class asio_generic_server
{
using shared_handler_t = std::shared_ptr<ConnectionHandler>;
public:
	asio_generic_server(int thread_count=1)
        : thread_count_(thread_count)
        , acceptor_(io_service_)
        {}

	void handle_new_connection( shared_handler_t handler
                                , boost::system::error_code const & error )
	{
		if(error){ return; }
		handler->start();
		auto new_handler = std::make_shared<ConnectionHandler>(io_service_);
		acceptor_.async_accept( new_handler->socket()
                                , [=](boost::system::error_code const & ec)
                                {
                                    handle_new_connection( new_handler, ec);
                                }
		);
	}
	void start_server(uint16_t port)
	{
		auto handler = std::make_shared<ConnectionHandler>(io_service_);
		// set up the acceptor to listen on the tcp port
		asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();
		acceptor_.async_accept( handler->socket()
                                , [=](boost::system::error_code const & ec)
                                // , [=](auto ec)
                                {
                                    handle_new_connection(handler, ec);
                                }
		);
		// start pool of threads to process the asio events
		for(int i=0; i<thread_count_; ++i)
		{
            thread_pool_.emplace_back( [=]{io_service_.run();} );
		}

        io_service_.run();

        // while(1)
        // {}
	}
private:
	int thread_count_;
	std::vector<std::thread> thread_pool_;
	asio::io_service io_service_;
	asio::ip::tcp::acceptor acceptor_;
};

class chat_handler
: public std::enable_shared_from_this<chat_handler>
{
public:
	chat_handler(asio::io_service& service)
	: service_(service)
	, socket_(service)
	, write_strand_(service)
	{}
	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}
	void start()
	{
		read_packet();
	}
private:

	void read_packet();
    void read_packet_done( boost::system::error_code const & error
                            , std::size_t bytes_transferred );
	void queue_message(std::string message);
	void start_packet_send();
	void packet_send_done(boost::system::error_code const & error);

	void send(std::string msg)
	{
		service_.post( write_strand_.wrap( [&msg, me=shared_from_this()]()
		{
			me->queue_message(msg);
		} ));
	}

	asio::io_service& service_;
	asio::ip::tcp::socket socket_;
	asio::io_service::strand write_strand_;
	asio::streambuf in_packet_;
	std::deque<std::string> send_packet_queue;
};

#endif // __SERVER_H__
