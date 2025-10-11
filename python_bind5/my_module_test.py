import unittest
from peng_demo import peng

class TestMyExtension(unittest.TestCase):
    def test_add(self):
        self.assertEqual(my_extension.add(1, 2), 3)
        self.assertEqual(my_extension.add(10, 20), 30)

if __name__ == "__main__":
    unittest.main()