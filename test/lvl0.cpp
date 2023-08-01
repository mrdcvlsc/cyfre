#include <cassert>
#include <iostream>
#include "../include/cyfre.hpp"

int main() {
    constexpr size_t SIZE = 16;
    cyfre::vec<int, cyfre::fixed<SIZE>, cyfre::axis_t::x> vec1;
    cyfre::vec<int, cyfre::fixed<SIZE>, cyfre::axis_t::y> vec2;
    cyfre::vec<int, cyfre::dynamic, cyfre::axis_t::x> vec3(SIZE);
    cyfre::vec<int, cyfre::dynamic, cyfre::axis_t::y> vec4(SIZE);

    cyfre::vec<int, cyfre::fixed<SIZE>, cyfre::axis_t::x> vec5;
    cyfre::vec<int, cyfre::fixed<SIZE>, cyfre::axis_t::y> vec6;
    cyfre::vec<int, cyfre::dynamic, cyfre::axis_t::x> vec7(SIZE);
    cyfre::vec<int, cyfre::dynamic, cyfre::axis_t::y> vec8(SIZE);

    for (size_t i = 0; i < SIZE; ++i) {
        vec1[i] = vec2[i] = vec3[i] = vec4[i] = i + 1;
    }

    assert(vec1 == vec1);
    assert(!(vec1 == vec2));
    assert(vec1 == vec3);
    assert(!(vec1 == vec4));

    assert(vec2 == vec2);
    assert(!(vec2 == vec3));
    assert(vec2 == vec4);

    assert(vec3 == vec3);
    assert(!(vec3 == vec4));

    assert(vec1 == vec1);
    assert(!(vec2 == vec1));
    assert(vec3 == vec1);
    assert(!(vec4 == vec1));

    assert(vec2 == vec2);
    assert(!(vec3 == vec2));
    assert(vec4 == vec2);

    assert(vec3 == vec3);
    assert(!(vec4 == vec3));

    std::cout << "\nTests : PASSED - BLAS level 0\n";
    return 0;
}