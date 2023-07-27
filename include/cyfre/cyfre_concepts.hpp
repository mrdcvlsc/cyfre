#ifndef MRDCVLSC_CYFRE_CONCEPTS_HPP
#define MRDCVLSC_CYFRE_CONCEPTS_HPP

#include <concepts>

namespace cyfre {
    template <typename T>
    concept matrix_t = requires(T t) {
        typename T::AllocatorType;
        typename T::ScalarType;
        t.MajorOrder;
        t.matrix;
    };
}

#endif