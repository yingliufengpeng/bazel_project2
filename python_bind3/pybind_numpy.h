//
// Created by peng on 5/12/25.
//

#ifndef PYBIND_NUMPY_H
#define PYBIND_NUMPY_H

#include <pybind11/pybind11.h>

// Make std::vector<int> opaque
PYBIND11_MAKE_OPAQUE(std::vector<int>);

using int_vector = std::vector<int>;

void InitNumpyBinding(pybind11::module& m);
void InitSmartPoint(pybind11::module& m);
void InitCustomSmallPointer(pybind11::module& m);
void InitCustomException(pybind11::module& m);



#endif //PYBIND_NUMPY_H
