cmake_minimum_required(VERSION 3.10)
project(community VERSION 1.0)

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

add_executable(concept ${SOURCES_CC} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(concept ${Protobuf_LIBRARIES})
install(TARGETS concept DESTINATION bin)


include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
include(CPack)

