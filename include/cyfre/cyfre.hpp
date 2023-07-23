#ifndef MRDCVLSC_CYFRE_HPP
#define MRDCVLSC_CYFRE_HPP

#include "enums.hpp"
#include "heap_alloc.hpp"
#include "stack_alloc.hpp"

/*
        INCLUDES ALL FILES IN THE CYFRE LIBRARY
*/

/* compiler -D flags

CHECK_RANGE_DISABLE  -  Disable internal range checking, slightly speeds up the program (do not use in development)
CHECK_SHAPE_DISABLE  -  Disable internal shape checking of matricies in matrix operations, slightly speeds up the

*/

namespace cyfre {

  template <typename alloc_t = dynamic<float>, traversal ORDER = traversal::row_t>
  class mat : public alloc_t {
    private:
    public:

    mat() : alloc_t() {
    }

    mat(size_t rows, size_t cols) : alloc_t(rows, cols) {
    }

    static mat nullzero();

    static mat identity();

    static mat scalar();
  };

} // namespace cyfre

#include "../../src/cyfre/heap_alloc.cpp"
#include "../../src/cyfre/stack_alloc.cpp"

#endif