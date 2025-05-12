# -*- coding: utf-8 -*-
import unittest



import basic
import tools
from basic import Dog

class TestBasic(unittest.TestCase):

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


        # v3 = basic.call_go(Dachshund())
        # print(f'v3 : call value is {v3}')

        #
        v4 = basic.Husky()
        print(f'v4: call value is {basic.call_go(v4)}')

        #
        # class B(basic.Husky):
        #     def go(self, n):
        #         v = super().go(n)
        #         return f'{v} ___B'
        #
        #
        # v5 = B()
        # print(f'v5: call value  is {basic.call_go(v5)}')



    def test_example_instance(self):
        Example = basic.Example
        o = Example(4)
        print(f'o is {o}')


    def test_OwnsPythonObjects(self):

        OwnsPythonObjects = basic.OwnsPythonObjects

        o = OwnsPythonObjects()
        print(f'o is {o}')

        o.value = "44"
        print(f"o is {o}")



    def test_myMethod(self):
        o = basic.MyClass()
        o.myMethod(4)


    def test_points(self):
        import numpy as np
        # 调用 C++ 函数创建 Point 数组
        points = basic.create_points()

        # 打印数组
        print(points)  # 输出类似: [(1., 2.) (3., 4.) (5., 6.)] dtype=[('x', '<f4'), ('y', '<f4')]

        # 访问字段
        print(points['x'])  # 输出: [1. 3. 5.]
        print(points['y'])  # 输出: [2. 4. 6.]

        # 调用 C++ 函数处理 Point 数组
        basic.print_points(points)

        # 创建一个新的 Point 数组并传递给 C++
        new_points = np.array([(0.0, 0.0), (1.1, 2.2)], dtype=[('x', np.float32), ('y', np.float32)])
        basic.print_points(new_points)



    def test_py_demo(self):
        basic.test_py_demo()


    def test_return_bytes(self):
        o = basic.return_bytes()
        print(f'return_bytes is {o}')

        basic.utf8_test("I am a good man!")

if __name__ == '__main__':
    unittest.main()