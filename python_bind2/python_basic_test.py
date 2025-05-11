import unittest


import basic
import tools
from basic import Dog

class TestBasic2(unittest.TestCase):

    def test_add(self):
        m = 3 + 4


    def test_cccc(self):

        tools.add(4, 4)

        print(f'test ab ...')

    def test_call_go(self):

        d = basic.Dog()

        v = basic.call_go(d)
        print(f'v1 call value is {v}')

        class Cat(basic.Animal):
            def go(self, ntimes):
                return 'miao' * ntimes


        v2 = basic.call_go(Cat())
        print(f'v2 call value is {v2}')


        class Dachshund(Dog):
            def __init__(self):
                Dog.__init__(self)

            def go(self, ntimes):
                v = super().go(ntimes)
                return f'{v} {ntimes} ntimes'


        v3 = basic.call_go(Dachshund())
        print(f'v3 : call value is {v3}')



if __name__ == '__main__':
    unittest.main()