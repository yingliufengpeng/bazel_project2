

#include <iostream>
#include "basic.h"






int add(int i, int j) {
    std::cout << "python_bind4 ... i + j = " << i + j << std::endl;
    return i + j;
}


std::string add_str(const std::string& i, const std::string& j) {

    std::string result = std::string(i) + std::string(j);

    std::cout << "python_bind4 ... i + j = " << result << std::endl;
    return result;
}



