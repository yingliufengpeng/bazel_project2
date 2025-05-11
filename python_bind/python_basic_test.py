import unittest

import basic_tools

class TestBasic(unittest.TestCase):

    def test_add(self):
        self.assertEqual(basic_tools.add(1, 2), 3)
        self.assertEqual(basic_tools.add(2, 2), 4)


if __name__ == "__main__":
    unittest.main()