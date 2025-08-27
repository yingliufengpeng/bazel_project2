//
// Created by peng on 5/11/25.
//

#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>

struct Pet {
    enum Kind {
        Dog = 0,
        Cat,
    };

    struct Attributes {
        float age = 0;
    };


    Pet(const std::string &name, Kind type) : name(name), type(type) { }
    Pet(const std::string &name) : name(name), type(Dog) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    void show();

    void set(int age_) { age = age_; }
    void set(const std::string &name_) { name = name_; }

    std::string name;
    Kind type;
    int age;
    Attributes attr;

};



#endif //STRUCT_H
