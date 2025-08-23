import unittest

# import main

class TestBasic(unittest.TestCase):

    def test_add(self):
        import os
        # from fastapi import FastAPI
        # import gast
        import numpy as np
        print(f'xxxxx {np.__file__}')
        os.system(' pip list  ')
        m = 3 + 4



if __name__ == "__main__":
    unittest.main()