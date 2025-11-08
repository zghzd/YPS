#pragma once
#include <iostream>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;
void partsthefile(std::vector<std::string>will_partfiles);

void filemode(std::string inputpath, std::string filetype) {
	std::cout << "正在加载......" << std::endl;
	std::vector<std::string>fileinwp = getAllFiles(inputpath);
	std::cout << "\t已加载文件列表" << std::endl;
	std::cout << "\t文件列表分离...";
	std::vector<std::string>files;
	if (filetype != ".") {
		for (auto a : fileinwp) {
			auto b = getFileExtension(a);
			if (b == filetype) {
				files.push_back(a);
			}
		}
	}
	else {
		std::cout << "用户没有指定文件类型！，已跳过此步骤...";
		files = fileinwp;
		fileinwp.clear();
		fileinwp.shrink_to_fit();
	}
	std::cout << "...完成" << std::endl;
	std::cout << "加载完成" << std::endl;
	std::cout << "====================================================================================================" << std::endl;
	std::cout << "正在进行->文件复制" << std::endl;
	partsthefile(files);
	std::cout << "完成" << std::endl;
}

void partsthefile(std::vector<std::string>will_partfiles) {
	std::string workpath = "./";
	std::string fname, fname_c;
	std::string cre_dir;
	for (auto a : will_partfiles) {
		fname = a;
		file_write_c("./report/file_list.txt", fname + "\n");
		if ((getFileExtension(fname) == "") || (getFileExtension(fname) == " ")) {
			std::cout << "\t已跳过无扩展名文件:" << fname << std::endl;
			continue;
		}
		cre_dir = "temp/" + getFileExtension(fname);
		fs::create_directory(cre_dir);
		fname_c = workpath + "temp/" + getFileExtension(fname) + "/" + transPathToDot(fname);
		try{
			fs::copy_file(fname, fname_c, fs::copy_options::overwrite_existing);
		}
		catch (fs::filesystem_error& e) {
			std::cerr << "文件错误->无法复制:" << e.what() << std::endl;
		}
		std::cout << "\t复制:" + fname + "->" + fname_c << std::endl;
	}
}