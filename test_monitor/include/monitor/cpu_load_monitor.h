#pragma once

#include <string>

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class CpuLoadMonitor : public MonitorInter {
 public:
  CpuLoadMonitor() {}
  void UpdateOnce(monitor::proto::MonitorInfo* monitor_info);
  void Stop() override {}
  // 通过使用 override 关键字，可以确保该函数是对基类中的虚函数的正确覆盖

 private:
  float load_avg_1_;
  float load_avg_3_;
  float load_avg_15_;
};

}  // namespace monitor
