#include <iostream>
#include <cstdlib>
#include "log.h"
#include "file_compare.h"
#include "fileread_withkey.h"
#include "opengl.h"
#include "entropy.h"
#include "getsoexport.h"
#include "getdllexport.h"
#include "SmaliFilesProcessing.h"
#include "ProcessingCenter.h"

std::string my_date = time_now(1);
std::string run_time = time_now();

int main(int argc, char* argv[]) {
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
		//PathInitialize();
	}
	else {
		std::cout << "�޷�����" << std::endl;
		return 0;
	}
}