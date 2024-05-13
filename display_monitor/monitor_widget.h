#pragma once

#include <QStandardItemModel>
#include <QtWidgets>
#include <thread>
#include <string>

#include "cpu_load_model.h"
#include "cpu_softirq_model.h"
#include "cpu_stat_model.h"
#include "mem_model.h"
#include "net_model.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"


namespace monitor {
class MonitorWidget : public QWidget {
  Q_OBJECT
  // 只有加入了Q_OBJECT，才能使用QT中的signal和slot机制，而且Q_OBJECT要放在类的最前面
 public:
  explicit MonitorWidget(QWidget* parent = nullptr); // 不允许隐式转换
  ~MonitorWidget() {
    // stop_ = true;
    // if (thread_->joinable()) {
    //   thread_->join();
    // }
  }
  QWidget* ShowAllMonitorWidget(const std::string& name);
  QWidget* InitCpuMonitorWidget();
  QWidget* InitSoftIrqMonitorWidget();
  QWidget* InitMemMonitorWidget();
  QWidget* InitNetMonitorWidget();
  QWidget* InitButtonMenu(const std::string& name);
  // QWidget* InitMemMonitorWidget();

  void UpdateData(const monitor::proto::MonitorInfo& monitor_info);

 private slots:
  void ClickCpuButton();
  void ClickSoftIrqButton();
  void ClickMemButton();
  void ClickNetButton();

 private:
  QTableView* monitor_view_ = nullptr;
  QTableView* cpu_load_monitor_view_ = nullptr;
  QTableView* cpu_stat_monitor_view_ = nullptr;
  QTableView* mem_monitor_view_ = nullptr;
  QTableView* net_monitor_view_ = nullptr;
  // QTableView 是用于显示表格数据的小部件。通过这些指针，可以在程序中引用这些表格视图对象，并对它们进行操作，比如设置数据模型、调整列宽、设置样式等
  // 

  MonitorBaseModel* monitor_model_ = nullptr;
  CpuLoadModel* cpu_load_model_ = nullptr;
  CpuStatModel* cpu_stat_model_ = nullptr;
  MemModel* mem_model_ = nullptr;
  NetModel* net_model_ = nullptr;

  QStackedLayout* stack_menu_ = nullptr;

  // std::unique_ptr<std::thread> thread_;
  // bool stop = false;
};
}  // namespace monitor
