
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