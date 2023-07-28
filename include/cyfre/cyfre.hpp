/**
 *  @file   cyfre.hpp
 *  @brief  Core Header File Of Cyfre.
 *  @author mrdcvlsc
 ***********************************************/

#ifndef MRDCVLSC_CYFRE_HPP
#define MRDCVLSC_CYFRE_HPP

/*
        INCLUDES ALL FILES IN THE CYFRE LIBRARY
*/

/* compiler -D flags

CHECK_RANGE_DISABLE  -  Disable internal range checking, slightly speeds up the program (do not use in development)
CHECK_SHAPE_DISABLE  -  Disable internal shape checking of matricies in matrix operations, slightly speeds up the

*/

#include "enums.hpp"
#include "cyfre_concepts.hpp"

#include "heap_alloc.hpp"
#include "stack_alloc.hpp"
#include "matrix.hpp"

#include "../../src/cyfre/heap_alloc.cpp"
#include "../../src/cyfre/stack_alloc.cpp"
#include "../../src/cyfre/matrix.cpp"

#endif