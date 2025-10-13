//
// Created by peng on 10/13/25.
//
#include <iostream>

#include "MyCoroutine.h"
static PyObject* MyCoroutineTypeObj = NULL;  // 全局类型对象

// __await__ slot
PyObject* MyCoroutine_await(MyCoroutineObject* self) {
    // Import asyncio module
    PyObject *asyncio_mod = PyImport_ImportModule("asyncio");
    if (asyncio_mod == NULL) {
        return NULL;
    }

    // Get asyncio.Future class
    PyObject *future_class = PyObject_GetAttrString(asyncio_mod, "Future");
    Py_DECREF(asyncio_mod);
    if (future_class == NULL) {
        return NULL;
    }

    // Get the current event loop
    PyObject *loop = PyObject_CallMethod(asyncio_mod, "get_event_loop", NULL);
    if (loop == NULL) {
        Py_DECREF(future_class);
        return NULL;
    }

    // Create a Future instance
    PyObject *future = PyObject_CallNoArgs(future_class);
    Py_DECREF(future_class);
    Py_DECREF(loop);
    if (future == NULL) {
        return NULL;
    }

    // Set a result immediately (e.g., 42) for simplicity
    PyObject *result = PyLong_FromLong(self ->value);
    if (result == NULL) {
        Py_DECREF(future);
        return NULL;
    }
    PyObject *set_result = PyObject_CallMethod(future, "set_result", "(O)", result);
    Py_DECREF(result);
    if (set_result == NULL) {
        Py_DECREF(future);
        return NULL;
    }
    Py_DECREF(set_result);

    // Call Future.__await__ to get the iterator
    PyObject *await_method = PyObject_GetAttrString(future, "__await__");
    if (await_method == NULL) {
        Py_DECREF(future);
        return NULL;
    }
    PyObject *iterator = PyObject_CallNoArgs(await_method);
    Py_DECREF(await_method);
    Py_DECREF(future);
    if (iterator == NULL) {
        return NULL;
    }

    return iterator; // Return the iterator from Future.__await__
}


static PyType_Slot MyCoroutine_slots[] = {
    {Py_am_await, (void*)MyCoroutine_await},
    {0, NULL},
};

static PyType_Spec MyCoroutine_spec = {
    .name = "MyCoroutine",
    .basicsize = sizeof(MyCoroutineObject),
    .flags = Py_TPFLAGS_DEFAULT,
    .slots = MyCoroutine_slots,
};
PyObject* MyCoroutine_New(int value) {
    if (!MyCoroutineTypeObj) {
        MyCoroutineTypeObj = PyType_FromSpec(&MyCoroutine_spec);
        Py_INCREF(MyCoroutineTypeObj);
    }
    MyCoroutineObject* obj = PyObject_New(MyCoroutineObject, (PyTypeObject*)MyCoroutineTypeObj);
    obj->value = value;
    return (PyObject*)obj;
}
PyObject* InitMyCoroutinType(PyObject* m) {
    // 创建 DemoIterType
    if (!MyCoroutineTypeObj) {
        MyCoroutineTypeObj = PyType_FromSpec(&MyCoroutine_spec);
        Py_INCREF(MyCoroutineTypeObj);
    }
    if (!MyCoroutineTypeObj) {
        std::cout << "自定义的模块的初始化失败... in DemoIterTypeObj" << std::endl;

        Py_DECREF(m);
        return NULL;
    }

    return MyCoroutineTypeObj;
}