from typing import Callable

from . import sub_m

def hello(s: str) -> str:
    ...

class DemoValueDescriptor:

    def __get__(self, instance, owner):
        ...

    def __set__(self, instance, value):
        ...

class Demo_A2:

    x: DemoValueDescriptor

    def __init__(self, name: str=None):
        ...

    def __aiter__(self):
        ...


    def __anext__(self):
        ...
    def __await__(self):
        ...

    def increment(self, *args):
        ...

    value: int
    scale: float
    name: str
    dict1: dict
    dict3: dict


    def __iter__(self):
        ...


    def __next__(self) -> int:
        ...

class Demo_Iter:
    def __iter__(self):
        ...


    def __next__(self):
        ...


def set_callback(f: Callable) -> None:
    ...

def clear_callback():
    ...


def trigger_callback(arg):
    ...


def import_and_call_with_args(module: str, name: str, arg0: int, arg1: str):
    ...