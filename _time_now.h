#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

std::string time_now() {
	SYSTEMTIME time_now;
	GetLocalTime(&time_now);
	std::string _now = (std::to_string(time_now.wYear)
		+ "-" + std::to_string(time_now.wMonth)
		+ "-" + std::to_string(time_now.wDay)
		+ "\t"
		+ std::to_string(time_now.wHour)
		+ ":" + std::to_string(time_now.wMinute)
		+ ":" + std::to_string(time_now.wSecond)
		+ "." + std::to_string(time_now.wMilliseconds));
	return _now;
}