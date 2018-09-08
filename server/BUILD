cc_binary(
    name = "server",
    srcs = [ "src/server.cpp",
             "src/main.cpp",
             "include/server.hpp"
            ],
    copts = [ "-Wall --std=c++14" ],
    includes = [ "include" ],
    linkopts = [ "-lpthread",
                 "-lboost_thread",
                 "-lboost_system",
                 "-lboost_filesystem",
                 "-lboost_program_options"
                ],
)
