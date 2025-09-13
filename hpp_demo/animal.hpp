
#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <ostream>


namespace animal {

    template<typename T>
    struct Person {
        T a;

        void show() {
            std::cout << a << std::endl;
        }
    };



}




#endif
