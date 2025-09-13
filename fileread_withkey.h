#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length() - 1;

    while (start <= end && std::isspace(static_cast<unsigned char>(str[start])))
        ++start;

    while (end >= start && std::isspace(static_cast<unsigned char>(str[end])))
        --end;

    if (start > end)
        return "";

    return str.substr(start, end - start + 1);
}
std::string getConfigValue(const std::string& filename, const std::string& projectName) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        size_t delimiter_pos = std::string::npos;
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == ':' || line[i] == '=') {
                delimiter_pos = i;
                break;
            }
        }

        if (delimiter_pos == std::string::npos)
            continue;

        std::string key = trim(line.substr(0, delimiter_pos));
        std::string value = trim(line.substr(delimiter_pos + 1));

        if (key == projectName) {
            file.close();
            return value;
        }
    }

    file.close();
    return "";
}