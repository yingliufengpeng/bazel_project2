//
// Created by peng on 5/8/25.
//
#include <iostream>
#include "Animal.h"

void Animal::sayHello() {

	std::cout << "Hello World! " << name_ << std::endl;


}

Animal::Animal(std::string name) {
	name_ = std::forward<std::string>(name);
}
