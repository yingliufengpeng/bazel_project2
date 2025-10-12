from typing import Callable

from . import sub_m

def hello(s: str) -> str:
    ...



class Demo_A2:

    def increment(self):
        ...

    value: int


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