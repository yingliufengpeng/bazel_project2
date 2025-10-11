#include <Python.h>
#include <iostream>

int main(int argc, char** argv) {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        std::cerr << "Failed to initialize Python" << std::endl;
        return 1;
    }
    std::cout << "Python initialized" << std::endl;
    PyRun_SimpleString("print('Hello from embedded Python with Bazel module mode!')");
    PyRun_SimpleString("import sys; print('Python version:', sys.version)");
    PyRun_SimpleString("import os; print('os __file__:', os.__file__)");
    Py_Finalize();
    return 0;
}
