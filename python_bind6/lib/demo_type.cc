#include <Python.h>
#include <structmember.h>
#include <iostream>

#include "MyCoroutine.h"
#include "THPVariableMeta.h"
// ---------------- DemoObject ----------------
typedef struct {
    PyObject_HEAD
    int value;
    double scale;
    int counter;
    PyObject* name;
    PyObject* dict;
    PyObject* dict1;
} DemoObject;
// ----------------- 描述符对象 -----------------
typedef struct {
    PyObject_HEAD
    int value;  // 内部存储的整数
} DemoValueDescriptor;

// ---------------- DemoIter ----------------
typedef struct {
    PyObject_HEAD
    int current;
    int stop;
} DemoIter;

// ---------------- Demo_iter ----------------
static PyObject* Demo_iter(DemoObject* self);

// ---------------- DemoIter logic ----------------
static PyObject* DemoIter_iternext(DemoIter* self) {
    if (self->current >= self->stop) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
    PyObject* result = PyLong_FromLong(self->current);
    self->current++;
    return result;
}

// ---------------- DemoObject getters/setters ----------------
static PyObject* demo_get_value(DemoObject* self, void* closure) { return PyLong_FromLong(self->value); }
static int demo_set_value(DemoObject* self, PyObject* value, void* closure) {
    long v = PyLong_AsLong(value);
    if (PyErr_Occurred()) return -1;
    self->value = (int)v;
    return 0;
}

static PyObject* demo_get_dict1(DemoObject* self, void* closure) {
    Py_INCREF(self->dict1);
    return self->dict1;
}

static int demo_set_dict1(DemoObject* self, PyObject* value, void* closure) {
    if (!value) { Py_CLEAR(self->dict1); return 0; }
    if (!PyDict_Check(value)) { PyErr_SetString(PyExc_TypeError, "dict1 must be a dict"); return -1; }
    Py_INCREF(value);
    Py_XDECREF(self->dict1);
    self->dict1 = value;
    return 0;
}
static PyObject*
Demo_getattro(DemoObject* self, PyObject* name)
{
    const char* name_str = PyUnicode_AsUTF8(name);
    std::cout << "Demo_getattro called for: " << (name_str ? name_str : "<null>") << std::endl;

    if (PyUnicode_Check(name) && PyUnicode_CompareWithASCIIString(name, "__dict__") == 0) {
        if (self->dict == NULL) {
            PyErr_SetString(PyExc_AttributeError, "__dict__ is NULL");
            return NULL;
        }
        Py_INCREF(self->dict);
        return self->dict;
    }

    return PyObject_GenericGetAttr((PyObject*)self, name);
}
/* 方法示例 */
static PyObject* demo_increment(DemoObject* self, PyObject* args) {
    long delta = 1;  // 默认值为 1

    // 如果传入了参数，就解析；否则保持默认值
    if (!PyArg_ParseTuple(args, "|l", &delta)) {
        return NULL;  // 参数类型错误
    }

    self->value += delta;
    return PyLong_FromLong(self->value);
}


static PyGetSetDef Demo_getset[] = {
    {"value", (getter)demo_get_value, (setter)demo_set_value, "value", NULL},
    {"dict1", (getter)demo_get_dict1, (setter)demo_set_dict1, "dict1", NULL},
    {NULL}
};
static PyObject* Demo_await(DemoObject* self) {
    // return MyCoroutine_New(self-> value);
    return MyCoroutine_await((MyCoroutineObject*)MyCoroutine_New(self-> value));
}


static PyObject* Demo_aiter(DemoObject* self) {

    return (PyObject*)self;
}

static PyObject* Demo_anext(DemoObject* self) {
    if (self->counter < 5) {
        PyObject* coro = MyCoroutine_New(self->counter++);
        return coro;  // async for 内部会 await
    }

    PyErr_SetNone(PyExc_StopAsyncIteration);
    return NULL;
}



/* 方法表 */
static PyMethodDef Demo_methods[] = {
    {"increment", (PyCFunction)demo_increment, METH_VARARGS, "Increment value by 1"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};
static PyMemberDef Demo_members[] = {

    {"__dictoffset__", Py_T_PYSSIZET, offsetof(DemoObject, dict), 0},
    {"value", T_INT, offsetof(DemoObject, value), 0, "the numeric value"},
    {"scale", T_DOUBLE, offsetof(DemoObject, scale), 0, "scaling factor"},
    {"dict3",  T_OBJECT_EX, offsetof(DemoObject, dict1), 0, "dict 3(str)"},
    // {"__dict__",  T_OBJECT_EX, offsetof(DemoObject, dict), 0, "dict (str)"},
    {"name",  T_OBJECT_EX, offsetof(DemoObject, name), 0, "name (str)"},
    {NULL}  // 哨兵，必须以 NULL 结尾
};

static void Demo_dealloc(DemoObject* self)
{
    PyObject_GC_UnTrack(self);   // 1. 先让 GC 不再跟踪该对象
    Py_CLEAR(self->name);         // 2. 清理 PyObject* 成员
    Py_TYPE(self)->tp_free((PyObject*)self); // 3. 释放对象内存
}
static PyObject* Demo_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    DemoObject* self = (DemoObject*)type->tp_alloc(type, 0);
    if (!self)
        return NULL;

    self->value = 0;
    self->scale = 1.0;
    self->name = NULL;
    self->dict = PyDict_New();   // 初始化 __dict__
    self->dict1 = PyDict_New();  // 你自定义的 dict1

    if (!self->dict || !self->dict1) {
        Py_XDECREF(self->dict);
        Py_XDECREF(self->dict1);
        Py_DECREF(self);
        return NULL;
    }

    // PyObject_GC_Track(self);
    return (PyObject*)self;
}

static int Demo_init(DemoObject* self, PyObject* args, PyObject* kwds)
{
    const char* n = nullptr;
    if (!PyArg_ParseTuple(args, "|s", &n))
        return -1;

    if (n)
        self->name = PyUnicode_FromString(n);
    else
        self->name = PyUnicode_FromString("default");

    return 0;
}


static int
Demo_traverse(DemoObject* self, visitproc visit, void* arg)
{
    // 如果 name 不为 NULL，就告诉 GC：我持有它
    Py_VISIT(self->name);
    Py_VISIT(self->dict1);
    Py_VISIT(self->dict);
    return 0;
}

static int
Demo_clear(DemoObject* self)
{
    Py_CLEAR(self->name);
    Py_CLEAR(self->dict1);
    Py_CLEAR(self->dict);
    return 0;
}
// ---------------- Demo_iter ----------------
static PyObject* Demo_iter(DemoObject* self) {
    PyObject* iter_type = PyObject_GetAttrString((PyObject*)Py_TYPE(self), "DemoIterType");
    if (!iter_type) return NULL;

    DemoIter* iter = (DemoIter*)PyObject_CallObject(iter_type, NULL);
    Py_DECREF(iter_type);
    if (!iter) return NULL;

    iter->current = 0;
    iter->stop = self->value;
    return (PyObject*)iter;
}

// ---------------- DemoIter heap type ----------------
static PyType_Slot DemoIter_slots[] = {
    {Py_tp_iter, (void*)PyObject_SelfIter},
    {Py_tp_iternext, (void*)DemoIter_iternext},
    {0, NULL}
};

static PyType_Spec DemoIter_spec = {
    "demo.DemoIter",
    sizeof(DemoIter),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE,
    DemoIter_slots
};
// ---------------- Demo_str ----------------
static PyObject* Demo_str(PyObject* self) {
    DemoObject* obj = (DemoObject*)self;
    const char* name_str = PyUnicode_AsUTF8(obj -> name);

    return PyUnicode_FromFormat("%d, %s", obj->value, name_str);
}
// ---------------- Demo heap type ----------------
static PyType_Slot Demo_slots[] = {
    {Py_tp_dealloc, (void*)Demo_dealloc},
    {Py_tp_new, (void*)Demo_new},
    {Py_tp_init, (void*)Demo_init},
    {Py_tp_traverse, (void*)Demo_traverse},
    {Py_tp_clear, (void*)Demo_clear},
    {Py_tp_str, (void*)Demo_str},
    {Py_tp_getset, (void*)Demo_getset},
    {Py_tp_getattro, (void*)Demo_getattro},
    {Py_tp_members, (void*)Demo_members},
    {Py_tp_methods, (void*)Demo_methods},
    {Py_tp_iter, (void*)Demo_iter},
    {Py_am_aiter, (void*)Demo_aiter},
    {Py_am_anext, (void*)Demo_anext},
    {Py_am_await, (void*)Demo_await},

    {0, NULL}
};

static PyType_Spec Demo_spec = {
    "Demo_A2",
    sizeof(DemoObject),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,
    Demo_slots

};


// tp_descr_get
static PyObject* DemoValue_descr_get(DemoValueDescriptor* self, PyObject* obj, PyObject* type) {
    // printf("tp_descr_get called, value=%d\n", self->value);
    std::cout << "tp_descr_get called, value=" << self->value << std::endl;
    return PyLong_FromLong(self->value);
}

// tp_descr_set
static int DemoValue_descr_set(DemoValueDescriptor* self, PyObject* obj, PyObject* value) {
    if (!PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be int");
        return -1;
    }
    long v = PyLong_AsLong(value);
    self->value = (int)v;
    printf("tp_descr_set called, new value=%d\n", self->value);
    return 0;
}
static PyType_Slot DemoValueDescriptorType_slots[] = {
    {Py_tp_descr_get, (void*)DemoValue_descr_get},
    {Py_tp_descr_set, (void*)DemoValue_descr_set},
    {0, NULL}
};
static PyType_Spec DemoValueDescriptorType_spec = {
    "DemoValueDescriptor",
    sizeof(DemoValueDescriptor),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE | Py_TPFLAGS_BASETYPE,
    DemoValueDescriptorType_slots

};




static PyObject* sub_hello(PyObject* self, PyObject* args) {
    // 打印类型名
    PySys_WriteStdout("self type: %s\n", Py_TYPE(self)->tp_name);

    // 打印 repr(self)
    PyObject* repr = PyObject_Repr(self);
    if (repr) {
        PySys_WriteStdout("self = %s\n", PyUnicode_AsUTF8(repr));
        Py_DECREF(repr);
    } else {
        PySys_WriteStderr("Failed to get repr(self)\n");
        PyErr_Clear();  // 防止异常干扰
    }

    // 如果是模块，打印模块名
    if (PyModule_Check(self)) {
        PyObject* name = PyObject_GetAttrString(self, "__name__");
        if (name) {
            PySys_WriteStdout("module name = %s\n", PyUnicode_AsUTF8(name));
            Py_DECREF(name);
        }
    }
    Py_RETURN_NONE;
}

static PyMethodDef SubMethods[] = {
    {"hello", sub_hello, METH_NOARGS, "Print hello from C++ submodule"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef submodule_def = {
    PyModuleDef_HEAD_INIT,
    "basic.sub_m",  // 全限定名
    "C++ implemented submodule",
    -1,
    SubMethods,
};
PyMODINIT_FUNC PyInit_demo(PyObject* m) {
    // PyObject* m = PyModule_Create(&demo_module);
    PyObject* sub_m;
    std::cout << "的模块的初始化..." << std::endl;

    sub_m = PyModule_Create(&submodule_def);
    if (sub_m == NULL) {
        std::cout << "自定义的模块的初始化失败... in sub_m" << std::endl;
        return NULL;
    }

    if (PyModule_AddObject(m, "sub_m",  sub_m)) {
        std::cout << "自定义的模块的初始化失败... in sub_m 2" << std::endl;

        Py_DECREF(&sub_m);
        return NULL;
    }

    // 创建 DemoIterType
    PyObject* DemoIterTypeObj = PyType_FromSpec(&DemoIter_spec);

    if (!DemoIterTypeObj) {
        std::cout << "自定义的模块的初始化失败... in DemoIterTypeObj" << std::endl;

        Py_DECREF(m);
        return NULL;
    }

    if (PyModule_AddObject(m, "DemoIter", DemoIterTypeObj) < 0) {
        std::cout << "自定义的模块的初始化失败... in DemoIter" << std::endl;

        Py_DECREF(DemoIterTypeObj);
        return NULL;
    }

    // 创建 DemoType
    PyObject* DemoTypeObj = PyType_FromSpec(&Demo_spec);
    if (!DemoTypeObj) {
        std::cout << "自定义的模块的初始化失败... in DemoTypeObj" << std::endl;

        return NULL;

    }

    if (InitMyCoroutinType(m) == NULL) {
        std::cout << "自定义的模块的初始化失败... in InitMyCoroutinType" << std::endl;

        return NULL;
    }


    if (InitTHPVariableMeta(m) == NULL) {
        std::cout << "自定义的模块的初始化失败... in InitTHPVariableMeta" << std::endl;

        return NULL;
    }

    // 挂载 DemoIterType 到 DemoType 内
    if (PyObject_SetAttrString(DemoTypeObj, "DemoIterType", DemoIterTypeObj) < 0) {
        Py_DECREF(DemoTypeObj);
        Py_DECREF(DemoIterTypeObj);
        return NULL;
    }
    // 创建 DemoType
    PyObject* DemoValueDescriptorTypeObj = PyType_FromSpec(&DemoValueDescriptorType_spec);

    if (!DemoValueDescriptorTypeObj) {
        std::cout << "自定义的模块的初始化失败... in DemoValueDescriptorTypeObj" << std::endl;
        if (PyErr_Occurred()) {
            // 获取异常类型、值、traceback
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);  // 从全局异常获取并清空
            PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);

            PyObject* str_exc = PyObject_Str(pvalue);
            const char* msg = PyUnicode_AsUTF8(str_exc);

            std::cerr << "PyObject_SetAttrString failed: " << (msg ? msg : "<unknown>") << std::endl;

            Py_XDECREF(str_exc);
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
        }
        return NULL;
    }


    if (PyModule_AddObject(m, "Demo_A2", DemoTypeObj) < 0) {
        std::cout << "自定义的模块的初始化失败... in Demo_A2" << std::endl;

        Py_DECREF(DemoTypeObj);
        return NULL;
    }


    //创建描述符对象 only created in heap...
    // 创建描述符对象
    DemoValueDescriptor* desc = PyObject_New(DemoValueDescriptor, (PyTypeObject*)DemoValueDescriptorTypeObj);
    desc->value = 123;


    // 将描述符挂到 Demo 类型
    Py_INCREF(desc);
    if (PyObject_SetAttrString(DemoTypeObj, "x", (PyObject*)desc) < 0) {
        std::cout << "自定义的模块的初始化失败..." << std::endl;
        // 先检查是否有异常
        if (PyErr_Occurred()) {
            // 获取异常类型、值、traceback
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);  // 从全局异常获取并清空
            PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);

            PyObject* str_exc = PyObject_Str(pvalue);
            const char* msg = PyUnicode_AsUTF8(str_exc);

            std::cerr << "PyObject_SetAttrString failed: " << (msg ? msg : "<unknown>") << std::endl;

            Py_XDECREF(str_exc);
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
        }

        Py_DECREF(desc);

        return NULL;
    }

    Py_DECREF(desc);  // SetAttrString 会持有引用
    std::cout << "的模块的初始成功..." << std::endl;

    return m;
}
