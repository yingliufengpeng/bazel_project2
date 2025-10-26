//
// Created by peng on 2025/10/25.
//

#ifndef BAZEL_PROJECT2_UTILS_H
#define BAZEL_PROJECT2_UTILS_H
#include <iostream>
#include <mutex>
#include <atomic>


#ifdef USE_P_MATH

inline auto add(int a, int b) -> int {
    return a + b;
}
#endif


inline void P_ASSERT_IMPL(bool cond, const char* expr, const char* msg,
                     const char* file, int line) {
    if (!cond) {
        std::cerr << "Assertion failed: " << expr
                  << "\nMessage: " << msg
                  << "\nFile: " << file
                  << ", Line: " << line
                  << std::endl;
        std::abort();
    }
}

#define CONCAT_IMPL(a, b) a##b      // 真正拼接
#define CONCAT(a, b) CONCAT_IMPL(a, b)  // 先展开 a/b，再拼接

#define P_ASSERT(cond, msg) \
P_ASSERT_IMPL((cond), #cond, msg, __FILE__, __LINE__)

#define LOG(fmt, ...) \
do { \
    printf("[LOG] " fmt "\n", ##__VA_ARGS__); \
} while (0)

#define HELLO() std::cout << "Hello "
#define WORLD() std::cout << "World!"

#define SAY_HELLO_WORLD() \
do { \
    HELLO(); \
    WORLD(); \
    std::cout << std::endl; \
} while (0)

#define PRINT_VAR(name, value) \
std::cout << name << " = " << value << std::endl;

#define PRINT_DOUBLE(x) \
PRINT_VAR(#x, (x) * 2)


#define FUNC_NAME(name) func_##name

#define DEFINE_FUNC(name) \
void FUNC_NAME(name)() { \
    std::cout << "Function " #name " called!" << std::endl; \
}

DEFINE_FUNC(foo)
DEFINE_FUNC(bar)

#define LOG_IMPL(level, fmt, ...) \
do \
    fprintf(stderr, "[" level "] " fmt "\n", ##__VA_ARGS__); \
while (0)

#define LOG_WARN(fmt, ...)  LOG_IMPL("WARN", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG_IMPL("INFO", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_IMPL("ERROR", fmt, ##__VA_ARGS__)

#define DOUBLE(v) (v) * 2
#define DOUBLE(v) (v) * 2

#define PRINT(D, v) \
 printf("v %d\n", D(v))

#define PRINT_DOBLE(v) PRINT(DOUBLE, v)

#define MAKE_NAME(a, b) a##b
#define VAR1 100
#define VAR2 200
#define GET_VAR(n) MAKE_NAME(VAR, n)

#define VALUE 34

#define STR(x) #x
#define TO_STRING(x) STR(x)

#define MAKE_VAR(name) int CONCAT(name, __COUNTER__)

#define TRY \
try {

#define CATCH \
} catch (std::exception& e) { \
    std::cout << "Caught exception: " << e.what() << std::endl; \
  }


namespace peng {




    struct SafeCounter {
        mutable std::atomic<int> count = 0;

        void increment() const {
            count.fetch_add(1, std::memory_order_relaxed);  // ✅ 原子操作
        }
    };

}


namespace peng {




    struct LockedCounter {
        mutable int count = 0;
        mutable std::mutex mtx;  // 用于保护共享资源

        void increment() const {
            std::lock_guard<std::mutex> lock(mtx);
            count++;
        }
    };
}

#endif //BAZEL_PROJECT2_UTILS_H