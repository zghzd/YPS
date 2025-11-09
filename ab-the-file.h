#pragma once
#include "data_processing.h"

void ab_so() {
	std::string path_ab_so = "./outdir/so/";
	fs::create_directory(path_ab_so);
	if (!(is_dir_has_file("./temp/so/")))return;
	std::vector<std::string>v = getAllFiles("./temp/so/");
	for (auto a : v) {
		std::string cmdstr = "abso " + a + " " + path_ab_so;
		system(cmdstr.c_str());
	}
}
void ab_xml_android() {
	std::string path_ab_xml_android = "./outdir/axml/";
	fs::create_directory(path_ab_xml_android);
	if (!(is_dir_has_file("./temp/xml/")))return;
	std::vector<std::string>v = getAllFiles("./temp/xml/");
	for (auto a : v) {
		std::string cmdstr = "abaxml " + a + " " + path_ab_xml_android;
		system(cmdstr.c_str());
	}
}

void ab_mainact(){ 
	ab_so(); ab_xml_android();
}
