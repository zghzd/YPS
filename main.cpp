#include <iostream>
#include <cstdlib>
#include "_log.h"
#include "file_compare.h"
#include "fileread_withkey.h"
#include "opengl.h"
#include "entropy.h"

std::string __data = time_now(1);

int main() {
	_log(__data + ".log", "D", "0000-0001", "Ӧ�ó������߳�", "Ӧ�ó���ɹ�����������ɻ����ĳ�ʼ��");
	
	return 0;
}