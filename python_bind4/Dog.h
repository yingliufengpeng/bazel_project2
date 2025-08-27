//
// Created by peng on 5/11/25.
//

#ifndef DOG_H
#define DOG_H
#include "Pet.h"
#include "Dog.h"


struct Dog : Pet {
    Dog(const std::string &name) : Pet(name) { }
    std::string bark() const { return "woof!"; }
};


#endif //DOG_H
