#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include "log.h"
double FileEntropy(const std::string& filename, std::string my_date) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return -1.0;
    }
    std::vector<size_t> freq(256, 0);
    size_t totalBytes = 0;
    unsigned char byte;

    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        ++freq[byte];
        ++totalBytes;
    }
    file.close();
    if (totalBytes == 0) return 0.0;
    double entropy = 0.0;
    for (size_t i = 0; i < freq.size(); ++i) {
        if (freq[i] == 0) continue;
        double p = static_cast<double>(freq[i]) / totalBytes;
        entropy -= p * std::log2(p);
    }
    return entropy;
}