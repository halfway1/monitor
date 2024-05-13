#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

constexpr char kServerPortInfo[] = "0.0.0.0:50051"; // constexpr 表示该变量是一个编译时常量，可以在编译期间求值
// 服务器的地址为 0.0.0.0，表示监听所有网络接口
void InitServer() {
  grpc::ServerBuilder builder; // 创建一个 gRPC 服务器构建器对象
  builder.AddListeningPort(kServerPortInfo, grpc::InsecureServerCredentials()); // 身份验证
  // 向服务器构建器添加一个监听端口，使用不安全的服务器凭据。这意味着服务器将在指定的端口上监听来自客户端的连接请求，但不进行任何身份验证。

  monitor::GrpcManagerImpl grpc_server;
  builder.RegisterService(&grpc_server);
  // 将 GrpcManagerImpl 对象注册到服务器构建器中。这样，服务器将能够处理来自客户端的 gRPC 调用

  // start
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  // 使用服务器构建器构建服务器对象，并启动服务器。这将创建一个 gRPC 服务器，并在指定端口上开始监听客户端连接请求
  
  server->Wait();

  return;
}

int main() {
  InitServer();
  return 0;
}