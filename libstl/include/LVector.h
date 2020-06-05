#ifndef LITEC_LIBSTL_LVECTOR_H
#define LITEC_LIBSTL_LVECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _LVector LVector;
typedef struct _LVectorOps LVectorOps;      // The vtable class.
typedef struct _LVectorPrivMembers LVectorPrivMembers;    // The private members of the struct LVector.
typedef struct _LVectorInitArgs LVectorInitArgs;    // The struct of arguments for the lvector_init function.

typedef struct _LVectorIter LVectorIter;    // The iterator class.
typedef struct _LVectorIterOps LVectorIterOps;  // The iterator's vtable class.

#define TO_LVECTOR(__p) ((LVector *)(&__p))  // Casting a pointer of a subclass of LVector to (LVector *).

struct _LVector {
    LVectorPrivMembers *__priv;
    const LVectorOps *__vops;
};

// The vtable class.
struct _LVectorOps {
    void *(*init)(void *args);
    void  (*free)(void *self);

    void        *(*at)      (LVector *self, int pos);
    void        *(*front)   (LVector *self);
    void        *(*back)    (LVector *self);
    void        *(*data)    (LVector *self);
    LVectorIter (*get_iter) (LVector *self, int pos);

    LVectorIter (*begin)    (LVector *self);
    LVectorIter (*end)      (LVector *self);
    LVectorIter (*rbegin)   (LVector *self);
    LVectorIter (*rend)     (LVector *self);

    bool    *(*empty)       (LVector *self);
    size_t  (*size)         (LVector *self);
    size_t  (*capacity)     (LVector *self);
    void    (*reserve)      (LVector *self, size_t new_cap);
    void    (*shrink_to_fit)(LVector *self);

    void        (*clear)        (LVector *self);
    LVectorIter (*insert)       (LVectorIter iter, void *obj);
    LVectorIter (*insert_count) (LVectorIter iter, size_t count, void *obj);
    LVectorIter (*insert_seg)   (LVectorIter iter, void *first, void *last);
    LVectorIter (*emplace)      (LVectorIter iter, void *args);
    LVectorIter (*erase)        (LVectorIter iter);
    LVectorIter (*erase_seg)    (LVectorIter first, LVectorIter last);
    void        (*push_back)    (LVector *self, void *obj);
    void        (*emplace_back) (LVector *self, void *args);
    void        (*pop_back)     (LVector *self);
    void        (*resize)       (LVector *self, size_t count, void *args);
    void        (*swap)         (LVector *self, LVector *dest);
};

// The private members of the struct LVector.
struct _LVectorPrivMembers {
    size_t _size;
    size_t _elem_size;
    size_t _capacity;
    void *_at;
    void *(*_elem_init)(void *args);
    void *(*_elem_free)(void *obj);
};

// The struct of arguments for the lvector_init function.
struct _LVectorInitArgs {

};

#endif