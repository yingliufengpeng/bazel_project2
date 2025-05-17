//
// Created by peng on 17/5/2025.
//

#include <iostream>
#define MAKE_STRING(LEFT, MIDDLE, RIGHT) LEFT ## MIDDLE ## RIGHT

#define STRINGIFY(x) #x

// 强制展开 MAKE_NAME 后再字符串化
#define EXPAND_AND_STRINGIFY(x) STRINGIFY(x)
#define TO_STRING_NAME(left, middle, right) EXPAND_AND_STRINGIFY(MAKE_STRING(left, middle, right))

#define LOG_V(W) \
        std::cout << TO_STRING_NAME(W, __MIDDLE__, W) << std::endl;

int main() {


#ifdef CC_LOG
    std::cout << "Log Something in CC_LOG" << std::endl;

#endif

#ifdef PLATFORM_LINUX
    LOG_V(LINUX)

#elif PLATFORM_WINDOWS
    LOG_V(WINDOWS)
#endif



#ifdef ENABLE_METRICS
    std::cout << "ENABLE_METRICS  Something in ENABLE_METRICS" << std::endl;
#endif

#ifdef BASIC_LOG
    std::cout << "BASIC_LOG Something in BASIC_LOG" << std::endl;
#endif

    std::cout << "Hello, config setting " << std::endl;
    return 0;
}