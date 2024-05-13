#include "monitor_widget.h"

namespace monitor {

MonitorWidget::MonitorWidget(QWidget *parent) {}

// QWidget 类是所有窗口类的父类 (控件类是也属于窗口类)
QWidget *MonitorWidget::ShowAllMonitorWidget(const std::string& name) {
  QWidget *widget = new QWidget();
  stack_menu_ = new QStackedLayout();
  stack_menu_->addWidget(InitCpuMonitorWidget());
  stack_menu_->addWidget(InitSoftIrqMonitorWidget());
  stack_menu_->addWidget(InitMemMonitorWidget());
  stack_menu_->addWidget(InitNetMonitorWidget());
  // 创建一个 QWidget 对象，并将其存储在指针 widget 中，作为整个布局的父对象。
  // 创建一个 QStackedLayout 对象 stack_menu_，用于管理多个子部件的堆栈布局。
  // 使用 addWidget() 函数将四个子部件添加到堆栈布局中

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(InitButtonMenu(name), 1, 0);
  layout->addLayout(stack_menu_, 2, 0);
  widget->setLayout(layout);
  return widget;
  // 创建一个 QGridLayout 对象 layout，用于将按钮菜单和堆栈布局放置在窗口中。
  // 使用 addWidget() 函数将按钮菜单添加到布局的第一行。
  // 使用 addLayout() 函数将堆栈布局添加到布局的第二行。
  // 使用 setLayout() 函数将整个布局应用到 QWidget 对象中。
  // 返回指向 QWidget 对象的指针 widget
}

QWidget *MonitorWidget::InitButtonMenu(const std::string& name) {
  // char *name = getenv("USER");
  QPushButton *cpu_button = new QPushButton(QString::fromStdString(name) + "_cpu", this);
  QPushButton *soft_irq_button = new QPushButton(QString::fromStdString(name) + "_soft_irq", this);
  QPushButton *mem_button = new QPushButton(QString::fromStdString(name) + "_mem", this);
  QPushButton *net_button = new QPushButton(QString::fromStdString(name) + "_net", this);
  QFont *font = new QFont("Microsoft YaHei", 15, 40);
  cpu_button->setFont(*font);
  soft_irq_button->setFont(*font);
  mem_button->setFont(*font);
  net_button->setFont(*font);

  QHBoxLayout *layout = new QHBoxLayout(); // 横向布局
  layout->addWidget(cpu_button);
  layout->addWidget(soft_irq_button);
  layout->addWidget(mem_button);
  layout->addWidget(net_button);

  QWidget *widget = new QWidget();
  widget->setLayout(layout);

  connect(cpu_button, SIGNAL(clicked()), this, SLOT(ClickCpuButton()));
  connect(soft_irq_button, SIGNAL(clicked()), this, SLOT(ClickSoftIrqButton()));
  connect(mem_button, SIGNAL(clicked()), this, SLOT(ClickMemButton()));
  connect(net_button, SIGNAL(clicked()), this, SLOT(ClickNetButton()));

  return widget;
}

QWidget *MonitorWidget::InitCpuMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *cpu_load_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuLoad:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_load_monitor_view_ = new QTableView;
  cpu_load_model_ = new CpuLoadModel;
  cpu_load_monitor_view_->setModel(cpu_load_model_);
  cpu_load_monitor_view_->show();

  QLabel *cpu_stat_label = new QLabel(this);
  cpu_stat_label->setText(tr("Monitor CpuStat:"));
  cpu_stat_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_stat_monitor_view_ = new QTableView;
  cpu_stat_model_ = new CpuStatModel;
  cpu_stat_monitor_view_->setModel(cpu_stat_model_);
  cpu_stat_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(cpu_load_label, 3, 0);
  layout->addWidget(cpu_load_monitor_view_, 4, 0, 2, 2);

  layout->addWidget(cpu_stat_label, 1, 0, 1, 1);
  layout->addWidget(cpu_stat_monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitSoftIrqMonitorWidget() {
  QWidget *widget = new QWidget();
  QLabel *monitor_label = new QLabel(this);
  monitor_label->setText(tr("Monitor softirq:"));
  monitor_label->setFont(QFont("Microsoft YaHei", 10, 40));

  monitor_view_ = new QTableView;
  monitor_model_ = new MonitorBaseModel;
  QSortFilterProxyModel *sort_proxy = new QSortFilterProxyModel(this);  // 可排序
  sort_proxy->setSourceModel(monitor_model_);
  monitor_view_->setModel(sort_proxy); 
  monitor_view_->setSortingEnabled(true);  // 启用表格视图的排序功能，这样用户就可以点击表头对表格中的数据进行排序
  monitor_view_->show();

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(monitor_label, 1, 0);
  layout->addWidget(monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitMemMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *mem_label = new QLabel(this);
  mem_label->setText(tr("Monitor mem:"));
  mem_label->setFont(QFont("Microsoft YaHei", 10, 40));

  mem_monitor_view_ = new QTableView;
  mem_model_ = new MemModel;
  mem_monitor_view_->setModel(mem_model_);
  mem_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(mem_label, 1, 0);
  layout->addWidget(mem_monitor_view_, 2, 0, 1, 1);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitNetMonitorWidget() {
  QWidget *widget = new QWidget(); // 创建一个新的 QWidget 对象，这将是我们的网络监视小部件的容器

  QLabel *net_label = new QLabel(this); // 创建一个标签控件 QLabel，用于显示网络监视的标题
  net_label->setText(tr("Monitor net:"));
  net_label->setFont(QFont("Microsoft YaHei", 10, 40));

  net_monitor_view_ = new QTableView; // 创建一个表格视图控件 QTableView，用于显示网络监视信息
  net_model_ = new NetModel;
  net_monitor_view_->setModel(net_model_); // 将网络模型对象设置为表格视图的数据模型，以便表格视图可以显示网络监视信息
  net_monitor_view_->show(); // 显示表格视图，使其可见

  QGridLayout *layout = new QGridLayout(); // 创建一个网格布局管理器，用于安排小部件在 QWidget 内的位置

  layout->addWidget(net_label, 1, 0); // 将网络标签添加到网格布局中，位于第 1 行，第 0 列 
  layout->addWidget(net_monitor_view_, 2, 0, 1, 1); // 将网络监视表格视图添加到网格布局中，位于第 2 行，第 0 列，覆盖了 1 行和 1 列的空间

  widget->setLayout(layout);
  return widget;
}

void MonitorWidget::UpdateData(
    const monitor::proto::MonitorInfo &monitor_info) {
  monitor_model_->UpdateMonitorInfo(monitor_info);
  cpu_load_model_->UpdateMonitorInfo(monitor_info);
  cpu_stat_model_->UpdateMonitorInfo(monitor_info);
  mem_model_->UpdateMonitorInfo(monitor_info);
  net_model_->UpdateMonitorInfo(monitor_info);
}

void MonitorWidget::ClickCpuButton() { stack_menu_->setCurrentIndex(0); }
void MonitorWidget::ClickSoftIrqButton() { stack_menu_->setCurrentIndex(1); }
void MonitorWidget::ClickMemButton() { stack_menu_->setCurrentIndex(2); }
void MonitorWidget::ClickNetButton() { stack_menu_->setCurrentIndex(3); }
}  // namespace monitor
