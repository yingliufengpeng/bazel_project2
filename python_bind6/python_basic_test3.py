import unittest
import basic
import os
import anyio

class TestBasic(unittest.TestCase):
  
    def test_add(self):

        v = basic.Demo_A2('4')
        v.increment()
        v.value = 34

        v.a = v

        print(f'v is {v}')




if __name__ == "__main__":
    unittest.main()