
from typing import Protocol

class Person(Protocol):
    name: str
    age: int



def make_person() -> 'Person':
    ...