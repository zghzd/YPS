#include <iostream>
#include <Windows.h>
#include <vector>
#include "_log.h"
#include "base_io.h"
#include "file_compare.h"
#include "fileread_withkey.h"

static std::vector<std::string> filecompare(std::string in_file_name1, std::string in_file_name2);
int file_write_new(std::string file_name, std::string write_str);
std::string file_read(std::string file_name);
int file_write_c(std::string file_name, std::string write_str);
std::string getConfigValue(const std::string& filename, const std::string& projectName);
std::vector<std::string> _log(std::string log_type, std::string log_time, int log_code, std::string log_text);

int main() {
	
	return 0;
}