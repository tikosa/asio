#include "client.hpp"

#include <iostream>

void Client::connect(asio::ip::tcp::endpoint& ep)
{
    socket_.async_connect(ep, [me = shared_from_this()] (const system::error_code& ec){
                std::cout << ec.message() << std::endl;
                me->set_connected(ec ? false : true);
            } );
}
