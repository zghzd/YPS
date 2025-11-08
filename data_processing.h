#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string>processing_strpartition(std::string str, std::string partstr) {
    size_t pos = str.find(partstr);
    std::string part1 = "";
    std::string part2 = "";
    if (pos != std::string::npos) {
        part1 = str.substr(0, pos);
        part2 = str.substr(pos + partstr.length());
    }
    std::vector<std::string>parts = { part1,part2 };
    if ((part1 == "") || (part2 == "")) {
        parts = {};
    }
    return parts;
}

std::vector<std::string> getAllFiles(const fs::path& root) {
    std::vector<std::string> files;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

std::vector<std::string> filterFilesByExtension(
    const std::vector<std::string>& files,
    const std::string& fileextname) {

    std::vector<std::string> result;

    for (const auto& file : files) {
        fs::path filePath(file);
        std::string extension = filePath.extension().string();
        if (!extension.empty() && extension[0] == '.') {
            extension = extension.substr(1);
        }
        if (extension == fileextname) {
            result.push_back(file);
        }
    }

    return result;
}

std::string getFileExtension(const std::string& file) {
    fs::path filePath(file);
    std::string extension = filePath.extension().string();
    if (extension.empty() && filePath.filename().string()[0] == '.') {
        std::string filename = filePath.filename().string();
        if (filename.length() > 1) {
            return filename.substr(1);
        }
    }

    if (!extension.empty() && extension[0] == '.') {
        return extension.substr(1);
    }

    return extension;
}

std::string transPathToDot(const std::string path) {
    std::string result = path;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '\\') {
            result[i] = '/';
        }
    }
    size_t lastSlash = result.find_last_of('/');
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '/' && i != lastSlash) {
            result[i] = '.';
        }
    }
    if (lastSlash != std::string::npos) {
        result[lastSlash] = '_';
    }
    return result;
}

std::string removePrefix(const std::string& str, const std::string& prefix) {
    if (prefix.empty()) return str;
    if (str.length() < prefix.length()) return str;
    if (str.compare(0, prefix.length(), prefix) == 0) {
        return str.substr(prefix.length());
    }
    return str;
}