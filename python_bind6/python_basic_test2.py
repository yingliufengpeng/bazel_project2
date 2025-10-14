import unittest
import basic
import os
import anyio

class TestBasic(unittest.TestCase):
  
    def test_add(self):

        class Sub(basic.THPVariable):
            pass
        v = Sub()
        print(f'in test_add v is {v}')

    def test_memoryview(self):
        v = basic.Demo_A2('Peng')

        # 直接通过 memoryview 访问底层 C 数据
        mv = memoryview(v)
        print(mv)
        print(len(mv), flush=True)     # 8
        mv[0] = 65        # 修改底层 C 数组
        print(bytes(mv))   # b'A\x00\x00\x00\x00\x00\x00\x00'


        bs = bytearray(v)
        bs[1] = 66
        print(f'bs is {bs}')

        print(f'end in test_memoryview')


if __name__ == "__main__":
    unittest.main()