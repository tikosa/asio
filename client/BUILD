cc_binary(
    name = "client",
    srcs = [ "src/client.cpp",
             "src/main.cpp",
             "include/client.hpp"
            ],
    copts = [ "-g -Wall --std=c++14" ],
    includes = [ "include" ],
    linkopts = [ "-lpthread",
                 "-lboost_thread",
                 "-lboost_system",
                 "-lboost_filesystem",
                 "-lboost_program_options"
                ],
)
