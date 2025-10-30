#include <iostream>
#include <string>

#include "cpp_lib/lib.h"

int main() {

    Person* p2 = make_person_ptr();
    std::cout << "name: " << p2->name << ", age: " << p2->age << std::endl;
    free_person_ptr(p2);

    const char* s = rust_make_string();
    std::string msg(s);
    rust_free_string(s);
    std::cout << "C++ got: " << msg << std::endl;

    char* s1 = new char[100];
    s1[0] = 'a';
    s1[1] = 'b';
    s1[2] = 'c';
    s1[3] = '\0';


    auto s2 = std::string(s1);

    std::cout<< "s2 = " << s2 << std::endl;

    s1[0] = 'm';
    std::cout<< "s2 = " << s2 << std::endl;

    auto v2 = std::string(process_img("hello, world"));
    std::cout << "v2 = " << v2 << std::endl;


    return 0;
}
