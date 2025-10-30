import unittest
import io
import sys
import os
import rustlib


class TestBasic(unittest.TestCase):
  
    def test_add(self):
        print('ff', dir(rustlib))
        p = rustlib.Person2("Alice", 30)
        print(p.greet())  # Hello, Alice (30)




if __name__ == "__main__":
    unittest.main()