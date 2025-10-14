//
// Created by peng on 14/10/2025.
//

#ifndef THPVARIABLEMETA_H
#define THPVARIABLEMETA_H

#include <Python.h>


struct THPVariableMeta {
    PyHeapTypeObject base;
};


struct THPVariable {
    PyObject_HEAD
    PyObject* obj;
};

PyObject* InitTHPVariableMeta(PyObject* m);

#endif // THPVARIABLEMETA_H