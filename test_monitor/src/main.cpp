#pragma once
#include <memory>
#include <thread>
#include <vector>

#include "client/rpc_client.h"
#include "monitor/cpu_load_monitor.h"
#include "monitor/cpu_softirq_monitor.h"
#include "monitor/cpu_stat_monitor.h"
#include "monitor/mem_monitor.h"
#include "monitor/monitor_inter.h"
#include "monitor/net_monitor.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

int main() {
  std::vector<std::shared_ptr<monitor::MonitorInter>> runners_;
  // 定义了一个名为 runners_ 的成员变量，它是一个存储了 monitor::MonitorInter 类型的智能指针的向量。
  // MonitorInter 是一个抽象基类，表示监控器接口，而 runners_ 向量将用于存储各种不同类型的监控器对象
  // std::shared_ptr 用于管理监控器对象，因为监控器对象需要在多个地方使用，并且在不同的地方共享所有权
  // 它的作用是管理一个共享的对象，并且可以由多个 shared_ptr 共享所有权。当所有指向该对象的 shared_ptr 都被销毁时，对象才会被释放

  runners_.emplace_back(new monitor::CpuSoftIrqMonitor());
  runners_.emplace_back(new monitor::CpuLoadMonitor());
  runners_.emplace_back(new monitor::CpuStatMonitor());
  runners_.emplace_back(new monitor::MemMonitor());
  runners_.emplace_back(new monitor::NetMonitor());
  // 在 runners_ 向量的末尾插入了新的智能指针对象
  // emplace_back 的语法与 push_back 类似，但参数是构造新元素所需的参数。这些参数将直接传递给新元素的构造函数，从而在向量的末尾创建新元素

  monitor::RpcClient rpc_client_;
  char *name = getenv("USER");
  // 使用 getenv 函数获取了环境变量 "USER" 的值，并将其存储在名为 name 的字符指针中。该环境变量通常用于存储当前登录用户的用户名

  std::unique_ptr<std::thread> thread_ = nullptr;
  // std::unique_ptr 用于管理线程对象，因为线程对象只在这段代码中使用，且只有一个线程对象
  // 当 unique_ptr 被销毁时，它所管理的对象也会被销毁
  thread_ = std::make_unique<std::thread>([&]() {
    while (true) {
      monitor::proto::MonitorInfo monitor_info;
      monitor_info.set_name(std::string(name));
      for (auto& runner : runners_) {
        runner->UpdateOnce(&monitor_info);
      }

      rpc_client_.SetMonitorInfo(monitor_info);
      std::this_thread::sleep_for(std::chrono::seconds(3));
      // 当前线程将会休眠3秒钟
    }
  });
  // 这段代码创建了一个新的线程，并通过 std::make_unique 函数创建了一个新的 std::thread 对象，
  // 其中包含了一个 lambda 表达式。这个 lambda 表达式定义了线程的主体代码，是一个无限循环，用于不断更新监控信息并发送给 RPC 客户端

  thread_->join();
  // 确保程序在子线程运行的同时不会退出，直到子线程执行完成

  return 0;
}
