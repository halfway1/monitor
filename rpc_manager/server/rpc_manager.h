#pragma once

#include <grpcpp/support/status.h>

#include <unordered_map>
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class GrpcManagerImpl : public monitor::proto::GrpcManager::Service {
 public:
  GrpcManagerImpl();

  virtual ~GrpcManagerImpl();

  // 第一个::表示全局命名空间，它告诉编译器 grpc 是全局命名空间下的命名空间
  ::grpc::Status SetMonitorInfo(::grpc::ServerContext* context,
                                const ::monitor::proto::MonitorInfo* request,
                                ::google::protobuf::Empty* response);
  ::grpc::Status GetMonitorInfo(::grpc::ServerContext* context,
                                const ::google::protobuf::Empty* request,
                                ::monitor::proto::MonitorInfo* response);

 private:
  monitor::proto::MonitorInfo monitor_infos_;
};

}  // namespace monitor
