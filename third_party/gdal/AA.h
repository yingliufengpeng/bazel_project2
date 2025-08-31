//
// Created by peng on 31/8/2025.
//

#ifndef BAZEL_PROJECT2_AA_H
#define BAZEL_PROJECT2_AA_H

#include "zlib.h"

class AA {
public:
    int process(const char* filename) {
        return show_inner(filename);
    }

    int show_inner(const char* file_name);
};


#endif //BAZEL_PROJECT2_AA_H
