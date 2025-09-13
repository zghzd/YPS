#pragma once
//按项目读取文件中对应值
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // 用于 std::isspace

// 辅助函数：去除字符串两端的空白字符
std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length() - 1;

    // 找到第一个非空白字符
    while (start <= end && std::isspace(static_cast<unsigned char>(str[start])))
        ++start;

    // 找到最后一个非空白字符
    while (end >= start && std::isspace(static_cast<unsigned char>(str[end])))
        --end;

    // 如果整个字符串都是空白，则返回空字符串
    if (start > end)
        return "";

    return str.substr(start, end - start + 1);
}
//参数：文件名，项目名称   返回值：项目名称对应值
std::string getConfigValue(const std::string& filename, const std::string& projectName) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // 文件打开失败，返回空字符串
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        // 跳过空行
        if (line.empty())
            continue;

        // 查找分隔符位置
        size_t delimiter_pos = std::string::npos;
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == ':' || line[i] == '=') {
                delimiter_pos = i;
                break;
            }
        }

        // 如果没有找到分隔符，跳过该行
        if (delimiter_pos == std::string::npos)
            continue;

        // 分割项目名称和值
        std::string key = trim(line.substr(0, delimiter_pos));
        std::string value = trim(line.substr(delimiter_pos + 1));

        // 检查项目名称是否匹配
        if (key == projectName) {
            file.close();
            return value;
        }
    }

    file.close();
    return ""; // 未找到匹配项
}