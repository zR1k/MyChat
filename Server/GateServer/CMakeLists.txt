cmake_minimum_required(VERSION 3.10)
project(GATESERVER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定 vcpkg 工具链文件
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# 查找依赖库
find_package(Boost REQUIRED COMPONENTS asio beast filesystem system)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Threads REQUIRED)

# 检查依赖项是否找到
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost libraries not found!")
endif()

if (NOT Protobuf_FOUND)
    message(FATAL_ERROR "Protobuf not found!")
endif()

if (NOT gRPC_FOUND)
    message(FATAL_ERROR "gRPC not found!")
endif()

if (NOT jsoncpp_FOUND)
    message(FATAL_ERROR "JsonCpp not found!")
endif()

# 查找所有源文件
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")

# 查找所有 .proto 文件
file(GLOB PROTO_FILES "proto/*.proto")

# 设置生成目录
set(PROTO_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

# 获取 Protobuf 和 gRPC 的编译器和插件
set(PROTOBUF_PROTOC_EXECUTABLE ${Protobuf_PROTOC_EXECUTABLE})
set(GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# 生成 Protobuf 和 gRPC 代码
foreach(proto_file ${PROTO_FILES})
    get_filename_component(proto_name ${proto_file} NAME_WE)

    add_custom_command(
        OUTPUT "${PROTO_GEN_DIR}/${proto_name}.pb.cc" "${PROTO_GEN_DIR}/${proto_name}.pb.h"
               "${PROTO_GEN_DIR}/${proto_name}.grpc.pb.cc" "${PROTO_GEN_DIR}/${proto_name}.grpc.pb.h"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS --cpp_out="${PROTO_GEN_DIR}" --grpc_out="${PROTO_GEN_DIR}" --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE} -I "${CMAKE_CURRENT_SOURCE_DIR}/proto" "${proto_file}"
        DEPENDS "${proto_file}"
    )

    list(APPEND SRC_FILES 
        "${PROTO_GEN_DIR}/${proto_name}.pb.cc" 
        "${PROTO_GEN_DIR}/${proto_name}.grpc.pb.cc"
    )
endforeach()

# 添加可执行文件
add_executable(GATESERVER ${SRC_FILES})

# 配置生成文件的包含路径
target_include_directories(GATESERVER PRIVATE ${PROTO_GEN_DIR})

# 设置目标的编译定义
target_compile_definitions(GATESERVER PRIVATE _WIN32_WINNT=0x0601)

# 链接依赖库
target_link_libraries(GATESERVER 
    PRIVATE
    Boost::asio
    Boost::beast
    gRPC::grpc++
    protobuf::libprotobuf
    JsonCpp::JsonCpp
    Threads::Threads
    Boost::filesystem
    Boost::system
)
