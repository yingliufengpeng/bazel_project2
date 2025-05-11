import unittest
import basic

class MyTestCase2(unittest.TestCase):
    def test_something(self):
        # raise UserWarning("fsfs")
        self.assertEqual(basic.add(2, 2), 4)


if __name__ == '__main__':
    unittest.main()