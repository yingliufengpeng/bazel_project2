//
// Created by peng on 10/12/25.
//

#ifndef BAZEL_PROJECT2_TOOLS_H
#define BAZEL_PROJECT2_TOOLS_H



#include <iostream>
#include <functional>
#include  <memory>
#include "tools.h"


void import_and_call_with_args(const std::string &module_name,
                               const std::string &func_name,
                               int arg1,
                               const std::string &arg2);


#endif //BAZEL_PROJECT2_TOOLS_H