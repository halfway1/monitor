#include <QColor>
#include <QFont>

#include "monitor_inter.h"

namespace monitor {

QVariant MonitorInterModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role == Qt::FontRole) {
    return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
  }

  if (role == Qt::BackgroundRole) {
    return QVariant::fromValue(QColor(Qt::lightGray));
  }

  return QAbstractTableModel::headerData(section, orientation, role);
}
// 当 role 参数等于 Qt::FontRole 时，返回一个 QFont 对象，表示表头的字体。这里使用了 "Microsoft YaHei" 字体，字号为 10，加粗。
// 当 role 参数等于 Qt::BackgroundRole 时，返回一个 QColor 对象，表示表头的背景色。这里使用了浅灰色。
// 对于其他 role 参数，调用基类 QAbstractTableModel 的 headerData() 函数，保持默认行为。

QVariant MonitorInterModel::data(const QModelIndex &index, int role) const {
  if (role == Qt::TextAlignmentRole) {
    return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
  }

  if (role == Qt::TextColorRole) {
    return QVariant::fromValue(QColor(Qt::black));
  }

  if (role == Qt::BackgroundRole) {
    return QVariant::fromValue(QColor(Qt::white));
  }

  return QVariant();
}
// 当 role 参数等于 Qt::TextAlignmentRole 时，返回一个 Qt::AlignmentFlag 枚举值，表示单元格文本的对齐方式。这里设置为左对齐且垂直居中。
// 当 role 参数等于 Qt::TextColorRole 时，返回一个 QColor 对象，表示单元格文本的颜色。这里设置为黑色。
// 当 role 参数等于 Qt::BackgroundRole 时，返回一个 QColor 对象，表示单元格的背景色。这里设置为白色。
// 对于其他 role 参数，返回一个空的 QVariant 对象，表示无需特殊处理。

}  // namespace monitor