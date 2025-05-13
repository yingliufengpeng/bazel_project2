
from typing import override
class Animal:
    ...


    @override
    def go(self, ntimes):
        ...


class Dog(Animal):
    ...

    @override
    def go(self, ntimes):
        ...


class Husky(Dog):
    @override
    def go(self, ntimes):
        ...

def call_go(m: Animal) -> str:

    ...


class Example:
    ...


class OwnsPythonObjects:
    ...


class MyClass:
    def myMethod(self, a):
        ...


class A:
    ...

class B:
    ...


def f(v):
    ...


def vectorized_func(l1, l2, l3):
    ...


def create_points():
    ...


def print_points(ls):
    ...


def test_py_demo():
    ...


def return_bytes() -> bytes:
    ...

def utf8_test(s: str):
    ...

class intVector:
    ...

    def push_back(self, e):
        ...


    def __len__(self):
        ...


    def __iter__(self):
        ...

    def pop_back(self):
        ...

IntVector = intVector

class Example2:
    ...

def create_example() -> Example2:
    ...

class Parent:
    ...
    def get_child(self) -> "Child":
        ...

class Child(Parent):
    ...

    def HelloWorld(self):...


class Person:
    value: ...


class MyCustomError:
    ...

def risky_function():
    ...