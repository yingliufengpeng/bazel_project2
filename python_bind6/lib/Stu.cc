//
// Created by peng on 11/10/2025.
//

#include <Python.h>

#include "Stu.h"

#define DEFERRED_ADDRESS(ADDR) nullptr

struct THPVariableMeta {
    PyHeapTypeObject base;
};

int THPVariableMetaType_init(PyObject* cls, PyObject* args, PyObject* kwargs) {
    return -1;
}


static PyTypeObject THPVariableMetaType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "torch._C._TensorMeta", /* tp_name */
    sizeof(THPVariableMeta), /* tp_basicsize */
    0, /* tp_itemsize */
    nullptr, /* tp_dealloc */
    0, /* tp_vectorcall_offset */
    nullptr, /* tp_getattr */
    nullptr, /* tp_setattr */
    nullptr, /* tp_reserved */
    nullptr, /* tp_repr */
    nullptr, /* tp_as_number */
    nullptr, /* tp_as_sequence */
    nullptr, /* tp_as_mapping */
    nullptr, /* tp_hash  */
    nullptr, /* tp_call */
    nullptr, /* tp_str */
    nullptr, /* tp_getattro */
    nullptr, /* tp_setattro */
    nullptr, /* tp_as_buffer */
    // NOLINTNEXTLINE(misc-redundant-expression)
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    nullptr, /* tp_doc */
    nullptr, /* tp_traverse */
    nullptr, /* tp_clear */
    nullptr, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    nullptr, /* tp_iter */
    nullptr, /* tp_iternext */
    nullptr, /* tp_methods */
    nullptr, /* tp_members */
    nullptr, /* tp_getset */
    nullptr, /* tp_base */
    nullptr, /* tp_dict */
    nullptr, /* tp_descr_get */
    nullptr, /* tp_descr_set */
    0, /* tp_dictoffset */
    THPVariableMetaType_init, /* tp_init */
    nullptr, /* tp_alloc */
    nullptr, /* tp_new */
};


bool initModule() {

    static struct PyModuleDef torchmodule = {
        PyModuleDef_HEAD_INIT, "torch._C", nullptr, -1, nullptr};
    auto module = PyModule_Create(&torchmodule);

    return true;

}