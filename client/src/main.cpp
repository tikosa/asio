#include "client.hpp"

#include <string>
#include <iostream>

namespace {
    const std::string host("127.0.0.1");
    const uint16_t port = 9001;
}

int main()
{
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(host), port);

    asio::io_service io_service_;
    shared_client_t client_ = std::make_shared<Client>(io_service_);
    client_->connect(ep);
    io_service_.run();

    std::cout << "is_connected " << client_->is_connected() << std::endl;

    return 0;
}
