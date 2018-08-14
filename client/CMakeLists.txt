cmake_minimum_required (VERSION 3.7)

project ( Client )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --std=c++14")
set (BOOST_ROOT $ENV{BOOST_ROOT})

file (GLOB HEADERS "include/*.hpp" )

add_executable( client
                src/client.cpp
                src/main.cpp
                ${HEADERS}
                )

target_link_libraries( client 
                       PUBLIC
                       pthread
                       boost_thread
                       boost_system
                       boost_filesystem
                       boost_program_options
                      )

target_include_directories( client 
                            PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include"
                            )
