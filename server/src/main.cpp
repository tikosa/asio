#include "server.hpp"

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>


namespace bpo = boost::program_options;

int main(int argc, char **argv)
{
    bpo::options_description options;
    options.add_options()
        ("file,f", bpo::value<boost::filesystem::path>(), "The file to send");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, options), vm);

    if(vm.count("file"))
        std::cout << vm["file"].as<boost::filesystem::path>() << std::endl;

    asio_generic_server<chat_handler> server;
    server.start_server(9001);

    return 0;
}
