cmake_minimum_required(VERSION 2.8.9)
project(concept)

find_package(Protobuf REQUIRED)

include_directories(inc)

#Adding Complier flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra")

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES_CC "src/*.cc")
file(GLOB SOURCES_PROTO "src/*.proto")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${SOURCES_PROTO})

add_executable(unimanage ${SOURCES_CC} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(unimanage ${Protobuf_LIBRARIES})

