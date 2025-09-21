#include <iostream>
#include <cstdlib>
#include "_log.h"
#include "file_compare.h"
#include "fileread_withkey.h"
#include "opengl.h"
#include "entropy.h"
#include "getsoexport.h"
#include "getdllexport.h"

std::string __date = time_now(1);

int main(int argc, char* argv[]) {
	_log(__date + ".log", "D", "0000-0001", "应用程序主线程", "应用程序成功启动且已完成基本的初始化");
	if (argc < 2) {
		std::cerr << "错误：参数过少" << std::endl;
		_log(__date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
		return -1;
	}

	if (std::string(argv[1]) == "filecompare") {
		if (argc < 4) {
			std::cerr << "错误：参数过少" << std::endl;
			_log(__date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = filecompare(argv[2], argv[3]);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << "\n";
		}
	}
	else if (std::string(argv[1]) == "getsoexport") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			_log(__date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = GetSoExports(argv[2], __date);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << "\n";
		}
	}
	else if (std::string(argv[1]) == "getdllexport64") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			_log(__date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = GetDllExports64(argv[2], __date);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << "\n";
		}
	}
	else if (std::string(argv[1]) == "opengl") {
		std::cout << "不支持" << std::endl;
	}
	else if (std::string(argv[1]) == "entropy") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			_log(__date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		double a = FileEntropy(argv[2], __date);
	}
	else {
		std::cout << "无法处理" << std::endl;
		return 0;
	}
}