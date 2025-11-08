#include <direct.h>
#include <regex>
#include <filesystem>
#include "log.h"
#include "copyright.h"
#include "data_processing.h"
#include "processingcenter.h"

namespace fs = std::filesystem;

std::string my_date = time_now(1);
std::string run_time = time_now_x1();
std::string workpath = "./";

std::string workmode = "selfcheck";
std::string filetype = ".";
std::string inputpath = "./";
std::string ypspackname = "";

int main(int argc, char* argv[]) {
	std::cout << copyright() << std::endl;
    std::vector<std::string> args;
    std::regex args_has(R"(^--(?!no\b)\w+-.+)");
    std::regex args_nohas(R"(^--no-\w+)");
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    for (auto v : args) {
        if (std::regex_match(v, args_has)) {
            v.erase(0, 2);
            std::vector<std::string>strparts = processing_strpartition(v, "-");
            if (strparts.empty()) {
                std::cerr << "错误的参数传递->" + v << std::endl;
                return 1;
            }
            if (strparts[0] == "mode") {
                workmode = strparts[1];
                std::cout << strparts[0] + "=" + strparts[1] << std::endl;
            }
            if (strparts[0] == "filetype") {
                filetype = strparts[1];
                std::cout << strparts[0] + "=" + strparts[1] << std::endl;
            }
            if (strparts[0] == "inputpath") {
                inputpath = strparts[1];
                std::cout << strparts[0] + "=" + strparts[1] << std::endl;
            }
            if (strparts[0] == "pack") {
                ypspackname = strparts[1];
                std::cout << strparts[0] + "=" + strparts[1] << std::endl;
            }
        }
        else if (std::regex_match(v, args_nohas)) {

        }
        else {

        }
    }
    const std::string dir_report = workpath + "report/";
    const std::string dir_temp = workpath + "temp/";
    const std::string dir_outdir = workpath + "outdir/";
    try{
    fs::create_directories(dir_report);
    fs::create_directories(dir_temp);
    fs::create_directories(dir_outdir);
    }catch(const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    std::vector<std::string>p_args = {
        workpath,
        workmode,
        filetype,
        inputpath,
        ypspackname
    };
    processingcenter(p_args);
}
