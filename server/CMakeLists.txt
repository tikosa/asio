cmake_minimum_required (VERSION 3.7)

project ( Server )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++14")
set (BOOST_ROOT $ENV{BOOST_ROOT})

file (GLOB HEADERS "include/*.hpp" )

add_executable( server
                src/server.cpp
                src/main.cpp
                ${HEADERS}
                )

target_link_libraries( server 
                       PUBLIC
                       pthread
                       boost_thread
                       boost_system
                       boost_filesystem
                       boost_program_options
                      )

target_include_directories( server 
                            PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include"
                            )
