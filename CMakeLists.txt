cmake_minimum_required(VERSION 3.10)

project(GATESERVER)

set(CMAKE_CXX_STANDARD 17)

# 如果使用vcpkg，指定toolchain
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg-master/scripts/buildsystems/vcpkg.cmake")

find_package(Boost REQUIRED COMPONENTS asio beast)
find_package(jsoncpp CONFIG REQUIRED)

add_definitions(-D_WIN32_WINNT=0x0601)

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")
add_executable(GATESERVER ${SRC_FILES})

target_link_libraries(GATESERVER 
    PRIVATE
    Boost::asio
    Boost::beast
    jsoncpp_lib
)