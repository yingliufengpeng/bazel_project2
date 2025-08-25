import unittest

import main

class TestBasic(unittest.TestCase):

    def test_add(self):
        import os
        from fastapi import FastAPI
        # import gast
        print(f'xxxx {main.app}')
        m = 3 + 4



if __name__ == "__main__":
    unittest.main()