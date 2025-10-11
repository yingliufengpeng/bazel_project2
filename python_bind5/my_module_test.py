import unittest
import libpeng_demo

print(f'xxxx {dir(libpeng_demo)} --- {dir(libpeng_demo.DemoObject)} >>>> {libpeng_demo.DemoObject.__name__}')

print(f'zzzz {libpeng_demo.__name__}')
class TestMyExtension(unittest.TestCase):
    def test_add(self):
        a = libpeng_demo.DemoObject()
        a.increment()
        print(f'a is {a.value}')

if __name__ == "__main__":
    unittest.main()