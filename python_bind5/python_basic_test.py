import unittest
import basic
import os

class TestBasic(unittest.TestCase):
  
    def test_add(self):
        print(f'current pwd is {os.getcwd()}')

        print(basic.hello('33'))
        v = basic.Demo_A2('Peng')
        #
        # v.x = 4
        v.value = 4
        v.m = 4
        #
        v.a = 34
        v.time = 'ok'
        #
        print(f"v'a is {v.a}")
        v._self = v
        print(f"v's __dict__ is {v.__dict__}")
        print(f'origin dict1 is {v.dict1}')
        v.dict1['d'] = 4
        print(f'after dict1 is {v.dict1}')


        print(f'v is {v} || name of v is {v.name}  ')
        v.dict3['dd'] = 5
        print(f'dict3 of v is {v.dict3}')

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

        v.increment()
        v.increment()


        v = basic.Demo_A2('Peng')

        v._self2 = v
        v.increment()
        v.increment()
        v.increment()
        v.name = '4'
        print(f'v name is {v.name}')
        # cc = v.__dict__
        # print(f"cc is {cc}", flush=True)
        print(f'dict1 is {v.dict1}', flush=True)
        print(f'dict1 is {v.dict1}', flush=True)
        print(f'dict1 is {v.dict1}', flush=True)


        print(f'__dict__ is {v.__dict__}')
        print(f'__dict__ is {v.__dict__}')


        v.increment()

    #


if __name__ == "__main__":
    unittest.main()