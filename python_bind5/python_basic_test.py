import unittest
import basic
import os

class TestBasic(unittest.TestCase):
  
    def test_add(self):
        print(f'current pwd is {os.getcwd()}')

        print(basic.hello('33'))
        # print(basic.DemoObject())
        v = basic.Demo_A2()
        v.increment()
        v.increment()
        v.increment()
        print(f'v is {v}')

        it = iter(v)
        print(f'iter is {it}')
        for e in it:
            print(f'e is {e}')

        v.increment()
        v.increment()
        print(v.value)

        sub_m = basic.sub_m
        print(f'sub_m = {sub_m}')

        sub_m.hello()

        def f(i):
            print(f'init ... {i}')

        basic.set_callback(f)

        basic.trigger_callback(342)

        # 程序退出前清理全局回调
        basic.clear_callback()

        basic.import_and_call_with_args("basic_tools", "greet", 35, "Alice")




if __name__ == "__main__":
    unittest.main()