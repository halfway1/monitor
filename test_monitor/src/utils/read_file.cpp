#include "utils/read_file.h"

namespace monitor {
bool ReadFile::ReadLine(std::vector<std::string>* args) {
  std::string line;
  // //line ="0.24 0.27 0.22 1/910 12216'
  std::getline(ifs_, line); // 将文件流 ifs_ 中的一行内容读取到 line 变量中
  if (ifs_.eof() || line.empty()) {
    return false;
  } // ifs_.eof() 来检查文件流是否已经到达文件尾（End Of File）

  // 从string对象line中读取字符
  std::istringstream line_ss(line);
  while (!line_ss.eof()) {
    std::string word;
    line_ss >> word; // >> 用于从输入流中读取数据，而 > 用于将输出流重定向到文件中
    // 默认情况下，>> 操作符在处理输入流时，会将空白字符（包括空格、制表符和换行符）作为分隔符，从而自动将单词按空白字符进行分割
    args->push_back(word);
  }
  return true;
}


}  // namespace monitor