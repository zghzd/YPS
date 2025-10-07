#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "log.h"
#include "copyright.h"
#include "file_compare.h"
#include "fileread_withkey.h"
#include "opengl.h"
#include "entropy.h"
#include "getsoexport.h"
#include "getdllexport.h"
#include "SmaliFilesProcessing.h"

std::string my_date = time_now(1);
std::string run_time = time_now();
void ExecStart(std::string my_date);

int exec_main(int argc, char* argv[]) {
	my_log(my_date + ".log", "D", "0000-0001", "应用程序主线程", "应用程序在" + run_time + "时间启动");
	if (argc < 2) {
		std::cerr << "错误：参数过少" << std::endl;
		my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
		return -1;
	}

	if (std::string(argv[1]) == "filecompare") {
		if (argc < 4) {
			std::cerr << "错误：参数过少" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = filecompare(argv[2], argv[3]);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << std::endl;
			if (argc >= 5 && std::string(argv[4]) == "-o") {
				file_write_c("filecompare.log", v[i] + "\n");
			}
		}
	}
	else if (std::string(argv[1]) == "getsoexport") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = GetSoExports(argv[2], my_date);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << std::endl;
			if (argc >= 4 && std::string(argv[3]) == "-o") {
				file_write_c(std::string(argv[2]) + ".export.txt", v[i] + "\n");
			}
		}
	}
	else if (std::string(argv[1]) == "getdllexport64") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		std::vector<std::string>v;
		v = GetDllExports64(argv[2], my_date);
		for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << std::endl;
			if (argc >= 4 && std::string(argv[3]) == "-o") {
				file_write_c(std::string(argv[2]) + ".export.txt", v[i] + "\n");
			}
		}
	}
	else if (std::string(argv[1]) == "opengl") {
		std::cout << "不支持" << std::endl;
	}
	else if (std::string(argv[1]) == "entropy") {
		if (argc < 3) {
			std::cerr << "错误：参数过少" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		double a = FileEntropy(argv[2], my_date);
		std::cout << a << std::endl;
	}
	else if (std::string(argv[1]) == "smalifilesprocessing") {
		if (argc < 4) {
			std::cerr << "错误：参数过少" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "应用程序主线程", "用户传递参数不合适");
			return -1;
		}
		SmaliFilesProcessing(argv[2], argv[3], my_date);
	}
	else if (std::string(argv[1]) == "start") {
		ExecStart(my_date);
	}
	else {
		std::cout << "无法处理" << std::endl;
		return 0;
	}
}

namespace fs = std::filesystem;

const fs::path RootDir = "./";
std::vector<fs::path>AllDir;
int PathInitialize() {
	int abdp = 0;
	fs::path bdp1 = "./temp/"; AllDir.push_back(bdp1);
	fs::path bdp2 = "./data/"; AllDir.push_back(bdp2);
	fs::path bdp3 = "./config/"; AllDir.push_back(bdp3);
	fs::path bdp4 = "./extended/"; AllDir.push_back(bdp4);
	int abdpn = 4;
	for (auto ap : AllDir) {
		if (fs::create_directory(ap)) {
			++abdp;
		}
	}

	if (abdp = abdpn) {
		return 0;
	}
	return 1;
}
int ExecInitialize() {
	int is_init = PathInitialize();
	if (is_init == 0)return 0;
	return 1;
}

void ExecStart(std::string my_date) {
	std::cout << copyright() << std::endl;
	std::cout << "是否需要初始化应用程序？(Y/N,y/n):";
	std::string need_init;
	std::cin >> need_init;
	if (need_init == "Y" || need_init == "y") {
		int is_init = ExecInitialize();
		if (is_init == 0) {
			std::cout << "初始化应用程序......成功" << std::endl;
			my_log(my_date + ".log", "D", "0000-0001", "shell", "成功初始化应用程序");
		}
		else {
			std::cout << "初始化应用程序失败" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "shell", "无法初始化应用程序");
			exit(0);
		}
	}
	std::string func_name;
	std::cout << "请输入功能(指令)名称:";
	std::cin >> func_name;
	if (func_name == "start")std::cout << "错误：你不能在当前状态下使用此功能" << std::endl;
	std::string func_argvs;
	std::cout << "请输入参数，注意，与常规输入方式不同，请以“|”作为分隔符而不是空格:";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, func_argvs);
	std::vector<char*> f_argvs_vector;
	f_argvs_vector.push_back(_strdup("yps"));
	f_argvs_vector.push_back(_strdup(func_name.c_str()));
	if (!func_argvs.empty()) {
		std::istringstream iss(func_argvs);
		std::string token;
		while (std::getline(iss, token, '|')) {
			size_t start = token.find_first_not_of(" \t");
			size_t end = token.find_last_not_of(" \t");

			if (start != std::string::npos && end != std::string::npos) {
				token = token.substr(start, end - start + 1);
			}

			if (!token.empty()) {
				f_argvs_vector.push_back(_strdup(token.c_str()));
			}
		}
	}
	f_argvs_vector.push_back(nullptr);
	char** f_argvs = f_argvs_vector.data();

	int f_argc = f_argvs_vector.size() - 1;
	exec_main(f_argc, f_argvs);
}