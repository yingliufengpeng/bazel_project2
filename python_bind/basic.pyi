
from typing import overload
def add(a, b) -> int:
    ...


the_answer = ...

world = ...

def get_static_data():
    ...

def print_dict(v: dict, *args, **kwargs):
    ...



class Data:
    ...

class Container:
    def __init__(self, data: Data):
        ...


    def get_data(self) -> Data:
        ...

from enum import Enum

class Pet:

    CAT = 0
    DOG = 1
    class Attributes:
        ...

    def __int__(self, name):
        ...

    def show(self):
        ...


    def setName(self):...

    def getName(self):...

    @overload
    def set(self, age: int):
        ...


    @overload
    def set(self, name: str):
        ...

class Dog:
    def __init__(self, name):
        ...

    def bark(self):
        ...

def pet_store(name: str) -> Pet:
    ...

def pet_store2():...