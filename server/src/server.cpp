#include "server.hpp"


void chat_handler::read_packet()
{
	asio::async_read_until( socket_,
                            in_packet_,
                            '\0',
                            [me=shared_from_this()]
                            ( boost::system::error_code const & ec
                            , std::size_t bytes_xfer)
                            {
                                me->read_packet_done(ec, bytes_xfer);
                            } );
}

void chat_handler::read_packet_done( boost::system::error_code const & error
                                    , std::size_t bytes_transferred )
{
    if(error){ return; }
    std::istream stream(&in_packet_);
    std::string packet_string;
    stream >> packet_string;
    // do something with it
    read_packet();
}

void chat_handler::queue_message(std::string message)
{
    bool write_in_progress = !send_packet_queue.empty();
    send_packet_queue.push_back(std::move(message));
    if(!write_in_progress)
    {
        start_packet_send();
    }
}

void chat_handler::start_packet_send()
{
    send_packet_queue.front() += "\0";
    async_write( socket_
                , asio::buffer(send_packet_queue.front())
                , write_strand_.wrap( [me=shared_from_this()]
                                        ( boost::system::error_code const & ec
                                        , std::size_t)
                                        {
                                            me->packet_send_done(ec);
                                        }
    ));
}

void chat_handler::packet_send_done(boost::system::error_code const & error)
{
    if(!error)
    {
    send_packet_queue.pop_front();
    if(!send_packet_queue.empty()){ start_packet_send(); }
    }
}
