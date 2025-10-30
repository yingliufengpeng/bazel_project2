import unittest
import basic
import os


class TestBasic(unittest.TestCase):
  
    def test_add(self):

        v = basic.make_person()

        del v


if __name__ == "__main__":
    unittest.main()