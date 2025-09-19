#pragma once
#include "base_io.h"
#include "_time_now.h"

int _log(std::string _path, std::string _type, std::string _code, std::string _what, std::string _infor) {
	std::string _time = time_now();
	std::string _log = ("["
		+ _time
		+ "]"
		+ _type + "-"
		+ _code + ":"
		+ _what
		+ "->"
		+ _infor
		+ "\n");
	if (_path == "" || _path == " ") {
		_path = ".log";
	}
	int c = file_write_c(_path, _log);
	return c;
}