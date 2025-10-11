import unittest
import basic



class TestBasic(unittest.TestCase):
  
    def test_add(self):

        print(basic.hello())
        # print(basic.DemoObject())
        v = basic.DemoObject()
        v.increment()
        v.increment()
        print(v.value)




if __name__ == "__main__":
    unittest.main()