#include "absl/strings/str_format.h"
#include "absl/container/inlined_vector.h"
#include "absl/memory/memory.h"

#include <iostream>

struct MyClass {

    MyClass() {
    std::cout << "MyCalss new ..." << std::endl;
    }

    void show() {
    std::cout << "MyCalss show ..." << std::endl;
    }

    ~MyClass() {
    std::cout << "MyCalss delete ..." << std::endl;
    }

};

int main() {
    std::unique_ptr<MyClass> ptr = absl::WrapUnique(new MyClass());

    ptr->show();


    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> ptr2 = ptr1;  // 引用计数增加

    std::cout << "Use count: " << ptr1.use_count() << "\n"; // 2

    std::string s = absl::StrFormat("Hello %s!", "Abseil");
    absl::InlinedVector<int, 4> vec = {1, 2, 3};
    vec.push_back(4);
    std::cout << s << " Vector size: " << vec.size() << std::endl;
}

