//
// Created by peng on 10/13/25.
//

#ifndef BAZEL_PROJECT2_MYCOROUTINE_H
#define BAZEL_PROJECT2_MYCOROUTINE_H

#include <Python.h>


typedef struct {
    PyObject_HEAD
    int value;  // 你希望 coroutine 返回的值
} MyCoroutineObject;
PyObject* MyCoroutine_await(MyCoroutineObject* self);

PyObject* MyCoroutine_New(int value);
PyObject* InitMyCoroutinType(PyObject* m);

#endif //BAZEL_PROJECT2_MYCOROUTINE_H