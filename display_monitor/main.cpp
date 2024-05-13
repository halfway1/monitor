#pragma once

#include <QApplication>
#include <thread>
#include "client/rpc_client.h"
#include "monitor_widget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  monitor::MonitorWidget moitor_widget;
  monitor::RpcClient rpc_client;
  monitor::proto::MonitorInfo monitor_info;
  // 创建一个 QApplication 对象 app，用于管理 Qt 应用程序的事件循环和其他全局状态。
  // 创建一个 monitor::MonitorWidget 对象 moitor_widget，用于显示监视器窗口。
  // 创建一个 monitor::RpcClient 对象 rpc_client，用于与远程服务器进行通信。
  // 创建一个 monitor::proto::MonitorInfo 对象 monitor_info，用于存储监视器信息

  //get board name
  rpc_client.GetMonitorInfo(&monitor_info); // 通过 RPC 客户端从服务器获取监视器信息，并存储在 monitor_info 对象中
  std::string name = monitor_info.name();

  QWidget* widget = moitor_widget.ShowAllMonitorWidget(name); // 创建一个监视器窗口的 QWidget 对象，并将其存储在 widget 指针中
  widget->show();

  std::unique_ptr<std::thread> thread_;
  thread_ = std::make_unique<std::thread>([&]() { // & 表示引用捕获，即 lambda 函数内部可以访问外部变量
    while (true) {
      monitor_info.Clear();
      rpc_client.GetMonitorInfo(&monitor_info);

      moitor_widget.UpdateData(monitor_info);
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  thread_->detach();

  return app.exec();
}