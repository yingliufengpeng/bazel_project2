//
// Created by peng on 9/21/25.
//
#include "foo.h"
#include "macros.h"   // 使用了宏

#include <iostream>

int foo() {
    DEBUG_PRINT("foo() called");
    return 42;
}
