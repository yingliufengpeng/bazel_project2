
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