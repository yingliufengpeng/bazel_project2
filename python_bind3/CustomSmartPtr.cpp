//
// Created by peng on 5/13/25.
//


#include <iostream>
#include <ostream>

template <typename T>
struct CustomSmartPtr {

private:
    T* ptr;
public:
    CustomSmartPtr(T *ptr): ptr(ptr) {
        std::cout << "CustomSmartPtr<T> auto memory managerment!!!" << std::endl;
    }
    virtual ~CustomSmartPtr() {
        // std::cout << "CustomSmartPtr<T> auto memory release!!!" << std::endl;
        delete ptr;
    }
    // 获取底层指针
    T* get() const { return ptr; }

};

struct Stu  {
    int value;
    Stu(int value): value(value) {}
    ~Stu() {
        std::cout << "Stu auto memory release stuck!!!" << std::endl;
    }

};


int main() {

    auto m = CustomSmartPtr(new Stu(10));
    std::cout << m.get()->value << std::endl;
}