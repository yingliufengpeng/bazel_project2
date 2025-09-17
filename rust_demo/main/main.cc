#include <iostream>

extern "C" int random_add(int);
extern "C" void make_person();

void foo() {
    std::cout << "Hello world!" << std::endl;
}

int main() {
    std::cout << "3 + random = " << random_add(3) << std::endl;
    make_person();
    foo();
    return 0;
}
