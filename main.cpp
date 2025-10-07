#include "ProcessingCenter.h"

int main(int argc, char* argv[]) {
	my_log(my_date + ".log", "D", "0000-0001", "应用程序主线程", "应用程序在" + run_time + "时间启动");
	return exec_main(argc, argv);
}
