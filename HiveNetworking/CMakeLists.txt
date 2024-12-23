set(CMAKE_CXX_STANDARD 20)

#vcpkg !?


#dependencies
add_subdirectory(dep/GameSockets)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(HiveNetworking ${SOURCES})
target_link_libraries(HiveNetworking GameNetworkingSockets)
target_include_directories(HiveNetworking PRIVATE src)

target_include_directories(HiveNetworking PRIVATE dep/GameSockets/src)