#pragma once
#include "base_io.h"
#include "time_now.h"

int my_log(std::string path, std::string type, std::string what, std::string infor) {
	std::string time = time_now_x1();
	std::string my_log = ("["
		+ time
		+ "]"
		+ type + ":"
		+ what
		+ "->"
		+ infor
		+ "\n");
	if (path == "" || path == " ") {
		path = time_now(1) + ".log";
	}
	int c = file_write_c(path, my_log);
	return c;
}