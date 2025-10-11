#include <Python.h>
#include <iostream>

int main(int argc, char** argv) {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        std::cerr << "Failed to initialize Python" << std::endl;
        return 1;
    }
    PyRun_SimpleString("print('Hello from embedded Python with Bazel module mode!')");
    PyRun_SimpleString("import sys; print('Python version:', sys.version)");
    Py_Finalize();
    return 0;
}
