#include <iostream>
#include <string>
#include <memory>
extern "C" {
    struct Person;
    void rust_free_string(const char* s);  // Rust 提供的释放函数
    const char* process_img(const char* s);  // Rust 提供的释放函数
    void free_inner_person_ptr(Person*);

    struct Person {
        const char *name;
        int age;

        ~Person() {
            if (name) free_inner_person_ptr(this);
            name = nullptr;
            std::cout << "Person destroyed" << std::endl;
        }
    };

    Person make_person();
    void rust_free_string(const char* s);  // Rust 提供的释放函数

    const char* rust_make_string();
    void rust_free_string(const char*);


    Person* make_person_ptr();
    void free_person_ptr(Person*);
}

struct CppPerson {
    std::shared_ptr<Person> person;  // 用 shared_ptr 管理内部 Person
    explicit CppPerson(std::shared_ptr<Person> p) : person(p) {}
};



