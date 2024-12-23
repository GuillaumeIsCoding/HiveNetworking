add_executable(Sandbox-Server main.cpp)

#dependencies
target_link_libraries(Sandbox-Server HiveNetworking)

target_include_directories(Sandbox-Server PRIVATE ${CMAKE_SOURCE_DIR}/HiveNetworking/src)
