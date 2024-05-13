#include "cpu_load_model.h"

namespace monitor {
CpuLoadModel::CpuLoadModel(QObject* parent) : MonitorInterModel(parent) {
  header_ << tr("load_1");
  header_ << tr("load_3");
  header_ << tr("load_15");
}

int CpuLoadModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int CpuLoadModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}

QVariant CpuLoadModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}

QVariant CpuLoadModel::data(const QModelIndex& index, int role) const {
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }
  // 检查列数是否在有效范围内，如果不在范围内则返回空的 QVariant

  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return QVariant();
}

void CpuLoadModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  beginResetModel(); // 这个函数用于通知视图，数据模型即将被重置。在这之后，视图会清空当前的数据，并等待新数据的到来
  monitor_data_.clear();

  monitor_data_.push_back(insert_one_cpu_load(monitor_info.cpu_load()));
  // 作用是将monitor_info中的CPU负载信息转换为适合在表格中显示的格式，并将其添加到monitor_data_中

  // QModelIndex leftTop = createIndex(0, 0);
  // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
  // emit dataChanged(leftTop, rightBottom, {});

  endResetModel();
  // 标志着模型重置的结束。此时，视图会重新从模型中获取数据，并根据新的数据进行更新显示

  return;
} 

std::vector<QVariant> CpuLoadModel::insert_one_cpu_load(
    const monitor::proto::CpuLoad& cpu_load) {
  std::vector<QVariant> cpu_load_list;
  for (int i = CpuLoad::CPU_AVG_1; i < COLUMN_MAX; i++) {
    switch (i) {
      case CpuLoad::CPU_AVG_1:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_1()));
        break;
      case CpuLoad::CPU_AVG_3:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_3()));
        break;
      case CpuLoad::CPU_AVG_15:
        cpu_load_list.push_back(QVariant(cpu_load.load_avg_15()));
        break;
      default:
        break;
    }
  }
  return cpu_load_list;
}
// 遍历了 CpuLoadModel 中定义的所有列，并根据列的索引从 monitor::proto::CpuLoad 中提取相应的数据
// 然后将提取的数据转换为 QVariant 类型，并添加到 cpu_load_list 中。最后返回 cpu_load_list。
}  // namespace monitor
