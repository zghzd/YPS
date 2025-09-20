#include <iostream>
#include <cstdlib>
#include "_log.h"
#include "file_compare.h"
#include "fileread_withkey.h"
#include "opengl.h"
#include "entropy.h"

std::string __data = time_now(1);

int main() {
	_log(__data + ".log", "D", "0000-0001", "应用程序主线程", "应用程序成功启动且已完成基本的初始化");
	
	return 0;
}