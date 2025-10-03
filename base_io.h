#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <windows.h>

//ÎÄ¼þÁ÷
int file_write_new(std::string file_name, std::string write_str) {
    
    std::ofstream outputFile;
    outputFile.open(file_name);
        if (outputFile.is_open()) {
            outputFile << write_str;
            outputFile.close();
            return 0;
            }
        else {
            return -1;
        }
    
}
std::string file_read(std::string file_name) {
    std::ifstream f(file_name.c_str());
        std::ifstream fin(file_name);
        if (f.good()) {
            goto file_good;
        }
        else {
            return "";
        }
    file_good:
        if (fin.is_open()) {
            std::stringstream buffer;
            buffer << fin.rdbuf();
            std::string str(buffer.str());
            fin.close();
            return str;
        }
        else
        {
            fin.close();
            return "";
        }
   
}


int file_write_c(std::string file_name, std::string write_str) {

    std::ofstream outputFile;
    outputFile.open(file_name, std::ios_base::app);
    if (outputFile.is_open()) {

        outputFile << write_str;
        outputFile.close();
        return 0;
    }
    else {
        return -1;
    }

}
