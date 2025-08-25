import unittest

import main

class TestBasic(unittest.TestCase):

    def test_add(self):
        import os
        import fastapi
        from fastapi import FastAPI
        # import gast
        print(f'xxxx {fastapi.__file__}')
        m = 3 + 4



if __name__ == "__main__":
    unittest.main()