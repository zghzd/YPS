#pragma once
#include "base_io.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#undef max
#include <Windows.h>

class my_compare {
private:
    std::string in_file_data_stringtext(std::string in_file_name) {
        std::cin >> in_file_name;
        return file_read(in_file_name);
    }
public:
    static std::vector<std::string> file_compare_stringtext(std::string in_file_name1, std::string in_file_name2) {
        std::vector<std::string> compare_an;
        my_compare text_0, text_1;
        std::string text_a = text_0.in_file_data_stringtext(in_file_name1);
        std::string text_b = text_1.in_file_data_stringtext(in_file_name2);
        std::replace(text_b.begin(), text_b.end(), '\r', '\n');
        std::vector<std::string>text_compare_b;
        std::vector<std::string>text_compare_a;
        std::stringstream ss_a(text_a);
        std::string line;
        while (std::getline(ss_a, line)) {
            text_compare_a.push_back(line);
        }

        std::stringstream ss_b(text_b);
        while (std::getline(ss_b, line)) {
            text_compare_b.push_back(line);
        }
        for (size_t i = 0; i < text_compare_b.size(); ++i) {
            if (text_a.find(text_compare_b[i]) != std::string::npos) {
                auto new_end = std::remove(text_compare_a.begin(), text_compare_a.end(), text_compare_b[i]);
                text_compare_a.erase(new_end, text_compare_a.end());
            }
            else {
                compare_an.push_back("+=" + text_compare_b[i]);
            }
        }
        for (size_t i = 0; i < text_compare_a.size(); ++i) {
            compare_an.push_back("-=" + text_compare_a[i]);
        }
        text_compare_b.clear();
        text_compare_a.clear();
        return compare_an;
    }
};


std::vector<std::string> filecompare(std::string in_file_name1, std::string in_file_name2) {
    std::vector<std::string> compare_an;
    compare_an = my_compare::file_compare_stringtext(in_file_name1, in_file_name2);
    return compare_an;
}
