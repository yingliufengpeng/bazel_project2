#include "animal.hpp"

int main() {
    auto m = animal::Person<int>();
    m.show();

    auto container = animal::Container<int, animal::Person>();
    auto m2 = container.getValue();
    m2->show();

}