#include <glog/logging.h>
#include <iostream>
#include "lib_a.h"

int main(int argc, char* argv[]) {
    // Initialize Google’s logging library.
    google::InitGoogleLogging(argv[0]);

    std::cout << "main in override_bazel module" << std::endl;

    LOG(INFO) << "Hello from the main module!";
    lib_a();
}
