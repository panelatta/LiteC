#ifndef LITEC_LIBSTL_LVECTOR_H
#define LITEC_LIBSTL_LVECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _LVector LVector;
typedef struct _LVectorOps LVectorOps;      // The vtable class.
typedef struct _LVectorPrivMembers LVectorPrivMembers;    // The private members of the struct LVector.
typedef struct _LVectorInitArgs LVectorInitArgs;    // The struct of arguments for the lvector_init function.

typedef struct _LVectorIter LVectorIter;    // The iterator class.

#define TO_VECTOR(__p) ((LVector *)(&__p))  // Casting a pointer of a subclass of LVector to (LVector *).

struct _LVector {
    LVectorPrivMembers *__priv;
    LVectorOps *__ops;
};

// The vtable class.
struct _LVectorOps {
    LVector *(*init)(LVectorInitArgs args);
    void *(*free)(LVector *self);

    bool *(*empty)(LVector *self);
    void *(*swap)(LVector *self);
    
};

// The private members of the struct LVector.
struct _LVectorPrivMembers {
    size_t size;
    size_t elem_size;
    size_t capacity;
    void *_at;
    void *_front;
    void *_back;
};

#endif