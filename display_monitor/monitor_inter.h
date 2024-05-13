#pragma once
#include <QAbstractTableModel>
#include <QObject>

namespace monitor {

class MonitorInterModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit MonitorInterModel(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {}
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
// data() 函数用于返回特定单元格的数据，可以用来自定义单元格的文本对齐方式、文本颜色、背景色等属性。
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
// headerData() 函数用于返回表头数据，可以用来自定义表头的字体、背景色等属性

  // override 是 C++11 中的一个关键字，用于显式地指示派生类中的虚函数重写了基类中的虚函数
  // 用于返回表头数据。根据参数 section 和 orientation 指定的行号和列号返回对应的表头数据。
  virtual ~MonitorInterModel() {}
  // 由于 QAbstractTableModel 的析构函数是虚函数，因此派生类的析构函数也应该声明为虚函数，以确保在删除基类指针时调用正确的析构函数
};

}  // namespace monitor