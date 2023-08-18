#include "cvector.h"


cvector_t* cvector_new(size_t elem_size)
{
    if (elem_size == 0)
        PANIC("element size must be > then 0");

    cvector_t* vec = malloc(sizeof(cvector_t));
    if (NULL == vec)
        PANIC("Unable to allocate vector");

    vec->elem_size = elem_size;
    vec->vec = NULL;
    vec->cap = 0;
    vec->size = 0;

    return vec;
}

void cvector_free(cvector_t* vec)
{
    if (NULL == vec)
        PANIC("vec is NULL");

    if (NULL != vec->vec)
        free(vec->vec);

    vec->elem_size = 0;
    vec->size = 0;
    vec->cap = 0;

    free(vec);
}

void cvector_push(cvector_t* vec, void* v)
{
    if (NULL == vec)
        PANIC("vec is NULL");

    if (NULL == v)
        PANIC("value is NULL");

    if (vec->size == 0)
    {
        vec->cap = 1;
        vec->vec = malloc(vec->cap * vec->elem_size);
    }
    
    if (vec->size == vec->cap)
    {
        vec->cap *= 2;
        vec->vec = realloc(vec->vec, vec->cap * vec->elem_size);
    }

    memcpy(&vec->vec[vec->size * vec->elem_size], v, vec->elem_size);
    ++vec->size;
}

void* cvector_pop(cvector_t* vec)
{
    if (NULL == vec)
        PANIC("vec is NULL");
    
    if (vec->size == 0)
        PANIC("vector is empty");

    return &vec->vec[--vec->size * vec->elem_size];
}

void* cvector_get(cvector_t* vec, size_t index)
{
    if (NULL == vec)
        PANIC("vec is NULL");
   
    if (index >= vec->size)
        PANIC("invalid index '%zu'", index);

    return &vec->vec[(vec->size - 1) * vec->elem_size];
}

void cvector_reserve(cvector_t* vec, size_t elem_count)
{
    if (NULL == vec)
        PANIC("vec is NULL");
  
    if (elem_count == 0)
        PANIC("requested elements count is 0");

    if (NULL == vec->vec)
    {
        vec->cap = elem_count;
        vec->vec = malloc(vec->cap * vec->elem_size);
        return;
    }

    vec->cap += elem_count;
    vec->vec = realloc(vec->vec, vec->cap * vec->elem_size);
}

void cvector_shrink(cvector_t* vec)
{
    if (NULL == vec)
        PANIC("vec is NULL");
    
    if (NULL == vec->vec || vec->size == vec->cap)
        return;

    vec->cap = vec->size;
    vec->vec = realloc(vec->vec, vec->cap * vec->elem_size);
}
