//
// Created by peng on 5/8/25.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>

class Animal {

private:
    std::string name_;

public:
    explicit Animal(std::string name);

    void sayHello();

    int32_t get_value() const {
        return 4;
    }

};

#endif //ANIMAL_H
