import unittest

import basic_tools

class TestBasic(unittest.TestCase):

    def test_add(self):
        self.assertEqual(basic_tools.add(1, 2), 3)
        self.assertEqual(basic_tools.add(2, 2), 4)



    def testPet(self):
        pet = basic_tools.Pet("44")
        pet.show()
        pet.name = "444"
        print(pet)

        pet.age = 4


    def test_Dog(self):
        dog = basic_tools.Dog("4")
        v = dog.bark()
        print('dog bark ' + v)


    def test_pet_store(self):
        o = basic_tools.pet_store("Dog11")
        print(f'object o is {o}')


    def test_pet_store2(self):
        o = basic_tools.pet_store2()
        print(f'obj is {o}')


    def test_override_pet(self):
        pet = basic_tools.Pet('o')

        pet.set(4)
        pet.set("44")
        print(pet)

    def test_pet_with_kind(self):
        pet = basic_tools.Pet('o', basic_tools.Pet.Cat)

        pet.show()




if __name__ == "__main__":
    unittest.main()