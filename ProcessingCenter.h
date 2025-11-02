#pragma once
#include "file_compare.h"
#include "fileread_withkey.h"
#include "load_pack.h"
#include "runmode-file.h"

/*
report/    temp/    outdir/
*/
/*
--workpath-<anypath>    ./
--mode-(selfcheck|file)    selfcheck
--filetype-<filetype>    .
--inputpath-<anypath>    ./
--pack-<packagename>    ""
*/

namespace fs = std::filesystem;

void processingcenter(std::vector<std::string>args) {
	if (args[4] != "") {

	}
	if (args[1] == "selfcheck") {

	}
	else if (args[1] == "file") {
		filemode(args[0], args[3], args[2]);
	}
	else {
		std::cerr << "无效的运行模式" << std::endl;
		return;
	}
}