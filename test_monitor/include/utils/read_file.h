#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace monitor {
class ReadFile {
 public:
  explicit ReadFile(const std::string& name) : ifs_(name) {}
  // 在构造函数中，通过成员初始化列表初始化了一个 std::ifstream 对象 ifs_，并将文件打开
  ~ReadFile() { ifs_.close(); }
  // explicit 关键字表明这是一个显式构造函数，即禁止隐式转换
  

  bool ReadLine(std::vector<std::string>* args);

  
  static std::vector<std::string> GetStatsLines(const std::string& stat_file,
                                                const int line_count) {
    std::vector<std::string> stats_lines;
    std::ifstream buffer(stat_file);  // 打开指定文件 stat_file 并创建一个 std::ifstream 对象 buffer，用于读取文件内容
    for (int line_num = 0; line_num < line_count; ++line_num) {
      std::string line;
      std::getline(buffer, line);
      if (line.empty()) {
        break;
      }
      stats_lines.push_back(line);
    }
    return stats_lines;
  }

 private:
  std::ifstream ifs_;
};
}  // namespace monitor
