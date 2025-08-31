
import  importlib

# basic = importlib.import_module('basic')

import basic

def get_name():
    return 'ok'

print_values = basic.print_values

def add(a, b):
    # s = basic.the_answer + ' ' + basic.world
    s = f'the {basic.world} is {basic.the_answer}'
    print(f' calling value is {s} ')
    return basic.add(a, b)


print_int = basic.print_int
printAllWrapper = basic.printAllWrapper

# basic.Pet.CAT
Pet = basic.Pet
Dog = basic.Dog
Data = basic.Data
Container = basic.Container
IntVector = basic.IntVector

print_dict = basic.print_dict
get_static_data = basic.get_static_data

pet_store = basic.pet_store
pet_store2 = basic.pet_store2