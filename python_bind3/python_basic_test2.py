# -*- coding: utf-8 -*-
import unittest



import basic
import tools
from basic import Dog

class TestBasic(unittest.TestCase):


    def test_smart_point(self):
        o = basic.create_example()
        print(f'test_smart_point o is {o}')


    def test_parent_child(self):
        Parent = basic.Parent
        Child = basic.Child
        print('parent_child begin ...')
        Parent().get_child().HelloWorld()
        print('parent_child end ...')


    def test_custom_smart_pointer(self):
        o = basic.Person(4)
        o.value = 44
        print(f'test_smart_pointer is {o.value}')



if __name__ == '__main__':
    unittest.main()