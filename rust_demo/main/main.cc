#include <iostream>
#include <string>

extern "C" {
    struct Person {
        const char* name;
        int age;
    };

    Person make_person();
    void free_person_name(const char* s);  // Rust 提供的释放函数
}

int main() {
    Person p = make_person();
    std::string name(p.name);
    std::cout << "Person name: " << name << ", age: " << p.age << std::endl;

    // 释放 Rust 分配的字符串
    free_person_name(p.name);

    std::cout << "finished" << std::endl;
    return 0;
}
