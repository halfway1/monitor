#include "rpc_client.h"

namespace monitor {
RpcClient::RpcClient() {
  auto channel = grpc::CreateChannel("192.168.67.155:50051",
                                     grpc::InsecureChannelCredentials());
  // 创建了一个到服务器地址 "localhost:50051" 的 gRPC 通道, 创建了一个不安全的 gRPC 通道凭证，表示不进行安全身份验证

  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
  // 创建了一个 gRPC 存根（stub）对象，该存根将消息发送到服务器的指定通道
}
RpcClient::~RpcClient() {}

void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info) {
  ::grpc::ClientContext context; // 用于设置 RPC 调用的上下文信息
  ::google::protobuf::Empty response; // 用于存储服务器响应的空消息
  ::grpc::Status status =
      stub_ptr_->SetMonitorInfo(&context, monito_info, &response); // 调用的是服务器的SetMonitorInfo方法
  // 使用 gRPC 存根对象 stub_ptr_ 的 SetMonitorInfo 方法发送监控信息到服务器，并获取调用状态 status

  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}

void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monito_info) {
  ::grpc::ClientContext context;
  ::google::protobuf::Empty request;
  ::grpc::Status status =
      stub_ptr_->GetMonitorInfo(&context, request, monito_info);
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}
}  // namespace monitor
