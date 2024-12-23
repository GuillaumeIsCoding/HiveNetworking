set(CMAKE_CXX_STANDARD 20)

#vcpkg !?
if (DEFINED ENV{VCPKG_ROOT})
    message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    if (DEFINED ENV{VCPKG_TARGET_TRIPLET})
        message(VERBOSE "VCPKG_TARGET_TRIPLET: $ENV{VCPKG_TARGET_TRIPLET}")
        set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_TARGET_TRIPLET}")
    endif()
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

#dependencies
add_subdirectory(dep/GameSockets)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(HiveNetworking ${SOURCES})
target_link_libraries(HiveNetworking GameNetworkingSockets)
target_include_directories(HiveNetworking PRIVATE src)

target_include_directories(HiveNetworking PRIVATE dep/GameSockets/src)