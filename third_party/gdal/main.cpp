#include <iostream>
#include "AA.h"
#include <filesystem>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>

//#include "external/bazel_tools/tools/cpp/runfiles/runfiles.h"
// #include "rules_cc/cc/runfiles/runfiles.h"
// #include "cc/runfiles/runfiles.h"


#include "gdal.h"



// using rules_cc::cc::runfiles::Runfiles;





int main(int argc, char *argv[]) {
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
    // std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0]));(argv[1]);
    // std::string real_path = runfiles->Rlocation(argv[1]);
    // auto file_name = real_path.c_str();
    auto file_name = argv[1];
    std::cout << "arc " << argc << " 传递进来的文件为: " << file_name << std::endl;

    auto obj = AA();
    auto res = obj.process(file_name);
//    auto res = obj.process("D:/repo/clion_repo/bazel_project2/third_party/gdal/WI_Poynette_801263_1901_62500_geo.tif");
    std::cout << "res is " << res << std::endl;
    return 0;
}
