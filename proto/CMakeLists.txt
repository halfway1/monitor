# 在项目中查找和配置 Protocol Buffers、gRPC 和 c-ares 库
# CONFIG 参数表示要查找的是配置文件（protobuf-config.cmake）
# REQUIRED 参数表示 Protocol Buffers 库是必需的，如果找不到，则会产生致命错误
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(c-ares CONFIG)
# find_package(Threads)



#
# Protobuf/Grpc source files
# 这段代码定义了一个名为 PROTO_FILES 的变量，其中包含了一组 Protocol Buffers 文件的名称。每个文件都是一个 .proto 文件，用于定义 Protocol Buffers 的消息类型。
# 这些 .proto 文件定义了不同类型的消息，并且可以用 Protocol Buffers 工具生成相应的代码
set(PROTO_FILES
    monitor_info.proto
    cpu_load.proto
    cpu_softirq.proto
    cpu_stat.proto
    mem_info.proto
    net_info.proto
)

#
# Add Library target with protobuf sources
# 创建了一个名为 monitor_proto 的库，该库由 ${PROTO_FILES} 变量中列出的一组 Protocol Buffers 文件构成
# 将 monitor_proto 库链接到一组依赖库上。其中，protobuf::libprotobuf、gRPC::grpc 和 gRPC::grpc++ 是外部库，它们提供了 Protocol Buffers 和 gRPC 相关的功能
add_library(monitor_proto ${PROTO_FILES})
target_link_libraries(monitor_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(monitor_proto PUBLIC
${PROTOBUF_INCLUDE_DIRS} 
${CMAKE_CURRENT_BINARY_DIR})
# 将一组头文件目录添加到 monitor_proto 库的包含路径中。${PROTOBUF_INCLUDE_DIRS} 表示 Protocol Buffers 的头文件目录，${CMAKE_CURRENT_BINARY_DIR} 表示当前构建目录

#
# Compile protobuf and grpc files in mointor proto target to cpp
# 用于获取 gRPC 的 C++ 插件的位置。grpc_cpp_plugin_location 变量将存储该位置

# 用于为 monitor_proto 目标生成 Protocol Buffers 的 C++ 代码 .pb.h  .pb.cc

# 用于为 monitor_proto 目标生成 gRPC 相关的代码。通过指定 LANGUAGE grpc 参数，生成的代码将包含 gRPC 相关的扩展。
# GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 参数用于指定生成的文件扩展名为 .grpc.pb.h 和 .grpc.pb.cc。
# PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}" 参数用于指定使用 protoc-gen-grpc 插件来生成 gRPC 相关的代码，其中 grpc_cpp_plugin_location 存储了该插件的位置
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET monitor_proto LANGUAGE cpp)
protobuf_generate(TARGET monitor_proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# 在这段代码中，并没有明确指定生成文件的路径。生成的文件将放置在默认的输出路径中，通常是在构建目录的相对路径下
# 构建目录的相对路径指的是在执行 CMake 构建时生成的构建文件所在的目录。通常，在执行 cmake 命令时，
# 会在源代码目录之外创建一个用于构建的目录，并在其中生成构建文件（如 Makefile、Visual Studio 项目文件等），然后在这个构建目录中执行编译和链接操作