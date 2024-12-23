add_executable(Sandbox-Client main.cpp)

#dependencies
target_link_libraries(Sandbox-Client HiveNetworking)

target_include_directories(Sandbox-Client PRIVATE ${CMAKE_SOURCE_DIR}/HiveNetworking/src)
