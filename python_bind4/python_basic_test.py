import unittest

import basic_tools

class TestBasic(unittest.TestCase):
  
    def test_add(self):
        m = 3 + 4



    def test_Pet(self):
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
        pet = basic_tools.Pet('343', basic_tools.Pet.Kind.Cat)
        # pet = basic_tools.Pet('343', )

        pet.show()


    def test_print_dict(self):
        d = {'name': "44", 'agre': 4}
        basic_tools.print_dict(d, 4, 5, a=4, b=5)


    def test_get_static_data(self):
        data = basic_tools.get_static_data()

        c = basic_tools.Container(data)


        print(f'data is {data}  data of c is {c.get_data()}')

    def test_VectorInt(self):
        v = basic_tools.IntVector()
        v.push_back(4)
        v.push_back(5)
        v.push_back(4)
        v.push_back(4)
        v.pop_back()
        print(f"test_VectorInt's lenght is {len(v)}")
        for e in v:
            print(f'e is {e}')

        print(f'type of v is {type(v)}')

    def test_print_values(self):
        ls = [2, 4, 5]
        basic_tools.print_values(ls)

if __name__ == "__main__":
    unittest.main()