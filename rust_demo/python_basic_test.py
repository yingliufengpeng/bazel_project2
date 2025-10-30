import unittest
import io

import basic
import os


class TestBasic(unittest.TestCase):
  
    def test_add(self):

        v = basic.make_person()

        del v

        src = 'aa bb cc'
        v = basic.process_img(src)
        print(f'src v is {src}')
        print(f'type(v):{type(v)}')
        print(f'v:', str(v))


if __name__ == "__main__":
    unittest.main()