import unittest
import basic

class MyTestCase2(unittest.TestCase):
    def test_something(self):
        import os

        print("Hello from Bazel!")
        print("RUNFILES_DIR =", os.environ.get("RUNFILES_DIR"))
        print("RUNFILES_MANIFEST_FILE =", os.environ.get("RUNFILES_MANIFEST_FILE"))

        self.assertEqual(basic.add(2, 2), 4)


if __name__ == '__main__':
    unittest.main()