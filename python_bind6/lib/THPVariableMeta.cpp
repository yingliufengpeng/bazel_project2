//
// Created by peng on 14/10/2025.
//
#include <iostream>

#include "THPVariableMeta.h"
static PyObject* THPVariableMetaObj = NULL;  // 全局类型对象


int THPVariableMetaType_init(PyObject* cls, PyObject* args, PyObject* kwargs) {
    std::cout << "THPVariableMetaType_init ... " << std::endl;
    if (PyType_Type.tp_init(cls, args, kwargs) < 0) {
        return -1;
    }

  return 0;
}

static PyObject* THPVariableMetaType_new(PyTypeObject* metacls, PyObject* args, PyObject* kwargs) {
    std::cout << "THPVariableMetaType_new called..." << std::endl;

    // 参数: name, bases, dict
    PyObject* name = nullptr;
    PyObject* bases = nullptr;
    PyObject* dict = nullptr;

    if (!PyArg_ParseTuple(args, "OOO:__new__", &name, &bases, &dict)) {
        return nullptr;
    }

    // 调用原始 type.__new__ 创建类型对象
    PyObject* type_obj = PyType_Type.tp_new(metacls, args, kwargs);
    if (!type_obj)
        return nullptr;

    std::cout << "THPVariableMetaType_new -> created type: "
              << PyUnicode_AsUTF8(PyObject_Str(name)) << std::endl;

    // 这里你可以对创建出来的类型做额外处理，比如：
    // - 修改 tp_flags
    // - 设置自定义属性
    // - 检查 bases 是否符合要求
    // - 记录类型信息
    // 举例：
    PyObject_SetAttrString(type_obj, "__created_by__", PyUnicode_FromString("THPVariableMeta"));

    return type_obj;
}



static PyType_Slot THPVariableMetaType_slots[] = {
    {Py_tp_new, (void*)THPVariableMetaType_new},
    {Py_tp_init, (void*)THPVariableMetaType_init},
    {Py_tp_base, (void*)&PyType_Type},
    {0, NULL},
};

static PyType_Spec THPVariableMeta_spec = {
    .name = "THPVariableMeta",
    .basicsize = sizeof(THPVariableMeta),
    .flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .slots = THPVariableMetaType_slots,
};

static int THPFake_traverse(THPVariable* self, visitproc visit, void* arg) {

    return 0;
}

static int THPFake_clear(THPVariable* self) {

    return 0;
}


static PyObject* THPVariable_new(PyTypeObject* type, PyObject* args, PyObject* kwargs);
static PyTypeObject THPVariableType = {
    PyVarObject_HEAD_INIT((PyTypeObject*)THPVariableMetaObj, 0)
    "THPVariableType", /* tp_name */
    sizeof(THPVariable), /* tp_basicsize */
    0, /* tp_itemsize */
    // This is unspecified, because it is illegal to create a THPVariableType
    // directly.  Subclasses will have their tp_dealloc set appropriately
    // by the metaclass
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
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
        Py_TPFLAGS_HAVE_GC, /* tp_flags */
    nullptr, /* tp_doc */
    // Also set by metaclass
    (traverseproc)THPFake_traverse, /* tp_traverse */
    (inquiry)THPFake_clear, /* tp_clear */
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
    nullptr, /* tp_init */
    nullptr, /* tp_alloc */
    // Although new is provided here, it is illegal to call this with cls ==
    // THPVariableMeta.  Instead, subclass it first and then construct it
    THPVariable_new, /* tp_new */
};

static PyObject* THPVariable_new(PyTypeObject* type, PyObject* args, PyObject* kwargs) {
    if (type == &THPVariableType) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot create 'THPVariableType' instances; subclass it first");
        return nullptr;
    }

    THPVariable* self = (THPVariable*)type->tp_alloc(type, 0);
    std::cout << "THPVariable_new (subclass) called!" << std::endl;
    return (PyObject*)self;
}

PyObject* InitTHPVariableMeta(PyObject* m) {
    std::cout << "自定义的模块的初始化  InitTHPVariableMeta"  << std::endl;
    // 创建 THPVariableMeta_spec
    if (!THPVariableMetaObj) {
        THPVariableMetaObj = PyType_FromSpec(&THPVariableMeta_spec);
        Py_INCREF(THPVariableMetaObj);
    }
    if (!THPVariableMetaObj) {
        std::cout << "自定义的模块的初始化失败... in DemoIterTypeObj" << std::endl;

        return NULL;
    }

    // 2. 设置 THPVariableType 的元类
    PyTypeObject* meta_type = (PyTypeObject*)THPVariableMetaObj;

    // PyVarObject_HEAD_INIT 设置初始时是 PyType_Type，
    // 我们现在要让它的 metaclass 指向自定义的 THPVariableMeta
    THPVariableType.ob_base.ob_base.ob_type = meta_type;

    if (PyType_Ready(&THPVariableType) < 0)
        return NULL;


    if (PyModule_AddObject(m, "THPVariableMeta", THPVariableMetaObj) < 0) {
        std::cout << "自定义的模块的初始化失败... in THPVariableMeta" << std::endl;

        Py_DECREF(THPVariableMetaObj);
        return NULL;
    }
    if (PyModule_AddObject(m, "THPVariable", (PyObject*)&THPVariableType) < 0) {
        std::cout << "自定义的模块的初始化失败... in THPVariable" << std::endl;

        return NULL;
    }
    std::cout << "自定义的模块的初始化成功  InitTHPVariableMeta"  << std::endl;

    return THPVariableMetaObj;
}