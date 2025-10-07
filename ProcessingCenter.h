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
	my_log(my_date + ".log", "D", "0000-0001", "Ӧ�ó������߳�", "Ӧ�ó�����" + run_time + "ʱ������");
	if (argc < 2) {
		std::cerr << "���󣺲�������" << std::endl;
		my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
		return -1;
	}

	if (std::string(argv[1]) == "filecompare") {
		if (argc < 4) {
			std::cerr << "���󣺲�������" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
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
			std::cerr << "���󣺲�������" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
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
			std::cerr << "���󣺲�������" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
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
		std::cout << "��֧��" << std::endl;
	}
	else if (std::string(argv[1]) == "entropy") {
		if (argc < 3) {
			std::cerr << "���󣺲�������" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
			return -1;
		}
		double a = FileEntropy(argv[2], my_date);
		std::cout << a << std::endl;
	}
	else if (std::string(argv[1]) == "smalifilesprocessing") {
		if (argc < 4) {
			std::cerr << "���󣺲�������" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "Ӧ�ó������߳�", "�û����ݲ���������");
			return -1;
		}
		SmaliFilesProcessing(argv[2], argv[3], my_date);
	}
	else if (std::string(argv[1]) == "start") {
		ExecStart(my_date);
	}
	else {
		std::cout << "�޷�����" << std::endl;
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
	std::cout << "�Ƿ���Ҫ��ʼ��Ӧ�ó���(Y/N,y/n):";
	std::string need_init;
	std::cin >> need_init;
	if (need_init == "Y" || need_init == "y") {
		int is_init = ExecInitialize();
		if (is_init == 0) {
			std::cout << "��ʼ��Ӧ�ó���......�ɹ�" << std::endl;
			my_log(my_date + ".log", "D", "0000-0001", "shell", "�ɹ���ʼ��Ӧ�ó���");
		}
		else {
			std::cout << "��ʼ��Ӧ�ó���ʧ��" << std::endl;
			my_log(my_date + ".log", "E", "0001-0000", "shell", "�޷���ʼ��Ӧ�ó���");
			exit(0);
		}
	}
	std::string func_name;
	std::cout << "�����빦��(ָ��)����:";
	std::cin >> func_name;
	if (func_name == "start")std::cout << "�����㲻���ڵ�ǰ״̬��ʹ�ô˹���" << std::endl;
	std::string func_argvs;
	std::cout << "�����������ע�⣬�볣�����뷽ʽ��ͬ�����ԡ�|����Ϊ�ָ��������ǿո�:";
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