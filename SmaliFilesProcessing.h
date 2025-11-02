#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "log.h"

namespace fs = std::filesystem;

std::string formatSmaliContent(const std::string& content) {
    std::string result;
    bool lastLineEmpty = false;
    size_t start = 0, end = 0;
    while (end != std::string::npos) {
        end = content.find('\n', start);
        std::string line = content.substr(start, (end == std::string::npos ? std::string::npos : end - start));
        while (!line.empty() && line.back() == '\r') line.pop_back();
        for (size_t pos = line.find('\t'); pos != std::string::npos; pos = line.find('\t', pos)) {
            line.replace(pos, 1, "    ");
            pos += 4;
        }
        if (line.empty()) {
            if (lastLineEmpty) {
                start = (end == std::string::npos ? end : end + 1);
                continue;
            }
            lastLineEmpty = true;
        }
        else {
            lastLineEmpty = false;
        }
        result += line + '\n';
        start = (end == std::string::npos ? end : end + 1);
    }
    return result;
}

std::vector<fs::path> getSmaliDirs(const std::string& srcRoot) {
    std::vector<fs::path> dirs;
    std::regex smali_classes_regex("^smali_classes[0-9]*$");
    for (const auto& entry : fs::directory_iterator(srcRoot)) {
        if (entry.is_directory()) {
            std::string dirname = entry.path().filename().string();
            if (dirname == "smali" || std::regex_match(dirname, smali_classes_regex)) {
                dirs.push_back(entry.path());
            }
        }
    }
    return dirs;
}

void SmaliFilesProcessing(const std::string& srcRoot, const std::string& dstRoot, std::string my_date) {
    std::vector<fs::path> smaliDirs = getSmaliDirs(srcRoot);
    for (const auto& srcDir : smaliDirs) {
        for (auto& p : fs::recursive_directory_iterator(srcDir)) {
            if (p.is_regular_file()) {
                std::string srcPath = p.path().string();
                std::string relPath = fs::relative(p.path(), srcDir).string();
                std::string dstPath = dstRoot + "/" + relPath;
                fs::create_directories(fs::path(dstPath).parent_path());
                std::ifstream fin(srcPath, std::ios::in);
                if (!fin) {
                    std::cerr << "无法打开: " << srcPath << std::endl;
                    continue;
                }
                std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
                fin.close();
                std::string formatted = formatSmaliContent(content);
                std::ofstream fout(dstPath, std::ios::out);
                if (!fout) {
                    std::cerr << "无法写入: " << dstPath << std::endl;
                    continue;
                }
                fout << formatted;
                fout.close();
                std::cout << "处理: " << srcPath << " -> " << dstPath << std::endl;
            }
        }
    }
}