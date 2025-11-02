#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "base_io.h"
#include "data_processing.h"

class load_pack {
private:
	void getpackinfor(std::string packname) {
		std::string packaddr = "./" + packname + "/" + packname + ".pack.yps";
		std::vector<std::string>ypspackfile = file_read_lines(packaddr);
		std::string ypspackhead = "YPS_PACK";
		std::string dever = processing_strpartition(ypspackfile[1], "|")[0];
		std::string fullpackname = processing_strpartition(ypspackfile[1], "|")[1];
		for (auto v : ypspackfile) {
			if (v.empty() || !(v.compare(0, ypspackhead.length(), ypspackhead) == 0)) {
				std::cout << "无效的包文件->packname" + packname << std::endl;
			}
			std::vector<std::string>packconfig = processing_strpartition(v, ">");
			if (packconfig[0] == "packageID-")static std::string packID = packconfig[1];
			if (packconfig[0] == "arguments-")static std::string arguments = packconfig[1];
			if (packconfig[0] == "load_exec-")static std::string loadexec = packconfig[1];
		}
	}

public:
	void loadpack(std::string packname) {
		getpackinfor(packname);

	}
};