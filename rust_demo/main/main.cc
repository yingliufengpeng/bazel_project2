#include <iostream>
#include <string>

#include "cpp_lib/lib.h"

int main() {
    Person p = make_person();
    std::string name(p.name);
    std::cout << "Person name: " << name << ", age: " << p.age << std::endl;

    // 释放 Rust 分配的字符串
    free_person_name(p.name);



    const char* s = rust_make_string();
    std::string msg(s);
    rust_free_string(s);
    std::cout << "C++ got: " << msg << std::endl;
    return 0;
}
