#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <memory>

#ifndef CLIENT_HPP
#define CLIENT_HPP

using namespace boost;

class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(asio::io_service& io_service)
        :socket_(io_service)
    {
    }

    void connect(asio::ip::tcp::endpoint& ep) ;

    bool is_connected() const { return is_connected_;}
private:
    void set_connected(bool c_) { is_connected_ = c_;}

    asio::ip::tcp::socket socket_;
    bool is_connected_ = false;
};

using shared_client_t = std::shared_ptr<Client>;

#endif // CLIENT_HPP
