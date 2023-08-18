#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include "clogging/clogging.h"

typedef struct 
{
    void* vec;
    size_t elem_size;
    size_t cap;
    size_t size;
} cvector_t;

// Allocates the new vector with specific element size
cvector_t* cvector_new(size_t elem_size);
// Frees the vector
void cvector_free(cvector_t* vec);

// Pushes the 'v' to the top of the vector
void cvector_push(cvector_t* vec, void* v);
// Removes the last element and returns it
void* cvector_pop(cvector_t* vec);
// Retunrs an element by a specific index
void* cvector_get(cvector_t* vec, size_t index);

// Reserves capacity for a specific elements count
void cvector_reserve(cvector_t* vec, size_t elem_count);
// Frees the unused capacity
void cvector_shrink(cvector_t* vec);


#endif // CVECTOR_H
