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


