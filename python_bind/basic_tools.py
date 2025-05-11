
import  importlib

# basic = importlib.import_module('basic')

import basic

def get_name():
    return 'ok'


def add(a, b):
    # s = basic.the_answer + ' ' + basic.world
    s = f'the {basic.world} is {basic.the_answer}'
    print(f' calling value is {s} ')
    return basic.add(a, b)


# basic.Pet.CAT
Pet = basic.Pet
Dog = basic.Dog

pet_store = basic.pet_store
pet_store2 = basic.pet_store2