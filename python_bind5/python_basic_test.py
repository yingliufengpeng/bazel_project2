import unittest
import basic



class TestBasic(unittest.TestCase):
  
    def test_add(self):

        print(basic.hello())
        # print(basic.DemoObject())
        v = basic.Demo_A2()
        print(f'v is {v}')
        v.increment()
        v.increment()
        print(v.value)

        sub_m = basic.sub_m
        print(f'sub_m = {sub_m}')

        sub_m.hello( )



if __name__ == "__main__":
    unittest.main()