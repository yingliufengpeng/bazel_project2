#include <iostream>
#include <string>

extern "C" {
    struct Person {
        const char* name;
        int age;
    };

    Person make_person();
    void free_person_name(const char* s);  // Rust 提供的释放函数

    const char* rust_make_string();
    void rust_free_string(const char*);
  }

int rust_free_string(int _cpp_par_);

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
