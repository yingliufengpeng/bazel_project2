
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

def call_go(m: Animal) -> str:

    ...