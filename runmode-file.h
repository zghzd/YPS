#pragma once
#include <iostream>
#include <regex>
#include <filesystem>

void partsthefile(std::vector<std::string>files);

void filemode(std::string workpath, std::string inputpath, std::string filetype) {
	std::cout << "正在加载......" << std::endl;
	std::vector<std::string>fileinwp = getAllFiles(inputpath);
	std::cout << "\t已加载文件列表" << std::endl;
	std::cout << "\t文件列表分离...";
	std::vector<std::string>files;
	if (filetype != ".") {
		for (auto a : fileinwp) {
			auto b = getFileExtension(a);
			if (b == filetype) {
				files.push_back(b);
			}
		}
	}
	else {
		std::cout << "用户没有指定文件类型！，已跳过此步骤..." << std::endl;
	}
	std::cout << "...完成" << std::endl;
	std::cout << "\t" << std::endl;

	std::cout << "加载完成" << std::endl;
}