#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "log.h"

namespace fs = std::filesystem;

const fs::path RootDir = "./";
std::vector<fs::path>AllDir;
void PathInitialize() {
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
		std::cout << "应用程序成功初始化" << std::endl;
		return;
	}
}