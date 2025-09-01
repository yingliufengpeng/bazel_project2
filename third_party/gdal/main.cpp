#include <iostream>

#include <filesystem>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>

//#include "external/bazel_tools/tools/cpp/runfiles/runfiles.h"
//#include "external/bazel_tools/tools/cpp/runfiles/runfiles.h"
#include "tools/cpp/runfiles/runfiles.h"

#include "third_party/gdal/impl/AA.h"
#include "gdal.h"

#include "impl/AA.h"

using rules_cc::cc::runfiles::Runfiles;


void help() {
#if defined(__clang__)
    std::cout << "Compiled with Clang "
              << __clang_major__ << "."
              << __clang_minor__ << "."
              << __clang_patchlevel__ << std::endl;
#elif defined(_MSC_VER)
    std::cout << "Compiled with MSVC, version " << _MSC_VER << std::endl;
#elif defined(__GNUC__)
    std::cout << "Compiled with GCC "
              << __GNUC__ << "." << __GNUC_MINOR__ << std::endl;
#else
    std::cout << "Unknown compiler" << std::endl;
#endif
}


int main(int argc, char *argv[]) {
    help();

    std::cout << "当前工作路径: " << std::filesystem::current_path() << std::endl;

    if (argc < 2) {
        std::cout << "参数传递错误  need file_name" << std::endl;
        return 0;
    }

    std::cout << "输入文件 :" << argv[1] << std::endl;
     std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0]));
//     std::string real_path = runfiles->Rlocation(argv[1]);
    const std::string workspace_prefix = "_main/";

     // std::string real_path = workspace_prefix + runfiles->Rlocation("third_party/gdal/WI_Poynette_801263_1901_62500_geo.tif");
     std::string real_path = runfiles->Rlocation( workspace_prefix + argv[1]);
     auto file_name = real_path.c_str();
//    auto file_name = argv[1];
    std::cout << "arc 22 " << argc << " 传递进来的文件为: " << file_name << std::endl;

    auto obj = AA();
    auto res = obj.process(file_name);
//    auto res = obj.process("D:/repo/clion_repo/bazel_project2/third_party/gdal/WI_Poynette_801263_1901_62500_geo.tif");
    std::cout << "res is " << res << std::endl;
    return 0;
}
