
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <memory>
#include <ostream>



namespace animal {

    template<typename T>
    struct Person {
        T a;

        void show() {
            std::cout << a << std::endl;
        }
    };


    template<typename T, template<typename> class Base>
    struct Container {

        auto getValue() {
            return std::unique_ptr<Base<T>>(new Base<T>());
        }
    };


}


#endif
