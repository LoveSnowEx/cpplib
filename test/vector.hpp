#include "../src/vector/vector.hpp"
#include <iostream>

void testVector() {
    Vector<int> v;
    for(int i = 0; i < 1'024; ++i) {
        v.pushBack(i);
        std::cout << v.size() << ' ' << v.cap() << '\n';
    }
    for(const auto &item : v) std::cout << item << '\n';
}