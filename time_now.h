#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

std::string time_now(int time_short = 0) {
	SYSTEMTIME time_now;
	GetLocalTime(&time_now);
	std::string now = (std::to_string(time_now.wYear)
		+ "-" + std::to_string(time_now.wMonth)
		+ "-" + std::to_string(time_now.wDay)
		+ "T"
		+ std::to_string(time_now.wHour)
		+ ":" + std::to_string(time_now.wMinute)
		+ ":" + std::to_string(time_now.wSecond)
		+ "." + std::to_string(time_now.wMilliseconds));
	std::string short_now = (std::to_string(time_now.wYear)
		+ "-" + std::to_string(time_now.wMonth)
		+ "-" + std::to_string(time_now.wDay));
	if (time_short != 0) {
		return short_now;
	}
	return now;
}

std::string time_now_x1(int time_short = 0) {
	auto now = std::chrono::system_clock::now();
	auto shanghai_time = std::chrono::zoned_time{ "Asia/Shanghai", now };

	return std::format("{:%Y-%m-%dT%H:%M:%S%z}", shanghai_time);
}