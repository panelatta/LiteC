#ifndef LITEC_LIBSTL_LVECTOR_H
#define LITEC_LIBSTL_LVECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include "LIter.h"

typedef struct _LVector LVector;
typedef struct _LVectorOps LVectorOps;      // The vtable class.
typedef struct _LVectorPrivMembers LVectorPrivMembers;    // The private members of the struct LVector.
typedef struct _LVectorInitArgs LVectorInitArgs;    // The struct of arguments for the function lvector_init.
typedef struct _LVectorIter LVectorIter;    // The iterator class.


struct _LVector {
    LVectorPrivMembers *__priv;
    const LVectorOps *__vops;
    unsigned int __errno;
};

// The vtable class.
struct _LVectorOps {
    void       *(*init)         (void *args);
    void        (*free)         (void *self);

    void       *(*at)           (LVector *self, size_t pos);
    void       *(*front)        (LVector *self);
    void       *(*back)         (LVector *self);
    void       *(*data)         (LVector *self);
    LVectorIter (*get_iter)     (LVector *self, size_t pos, bool is_reverse);

    LVectorIter (*begin)        (LVector *self);
    LVectorIter (*end)          (LVector *self);
    LVectorIter (*rbegin)       (LVector *self);
    LVectorIter (*rend)         (LVector *self);

    bool        (*empty)        (LVector *self);
    size_t      (*size)         (LVector *self);
    size_t      (*elem_size)    (LVector *self);
    size_t      (*capacity)     (LVector *self);
    void        (*reserve)      (LVector *self, size_t new_cap);
    void        (*shrink_to_fit)(LVector *self);

    void        (*clear)        (LVector *self);
    LVectorIter (*insert)       (LVectorIter iter, size_t count, void *obj);
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
    size_t elem_size;
    size_t capacity;
    void *(*elem_init)(void *);
    void *(*elem_free)(void *);
};

// The iterator class.
struct _LVectorIter {
    const RandomAccessIterOps *__vops;
    size_t elem_size;
    bool is_reverse;
    void *at;
};

// Functions of LVector.
void        *lvector_init           (void *args);
void         lvector_free           (void *self);

void        *lvector_at             (LVector *self, size_t pos);
void        *lvector_front          (LVector *self);
void        *lvector_back           (LVector *self);
void        *lvector_data           (LVector *self);
LVectorIter  lvector_get_iter       (LVector *self, size_t pos, bool is_reverse);

LVectorIter  lvector_begin          (LVector *self);
LVectorIter  lvector_end            (LVector *self);
LVectorIter  lvector_rbegin         (LVector *self);
LVectorIter  lvector_rend           (LVector *self);

bool         lvector_empty          (LVector *self);
size_t       lvector_size           (LVector *self);
size_t       lvector_elem_size      (LVector *self);
size_t       lvector_capacity       (LVector *self);
void         lvector_reserve        (LVector *self, size_t new_cap);
void         lvector_shrink_to_fit  (LVector *self);

void         lvector_clear          (LVector *self);
LVectorIter  lvector_insert         (LVector *self, size_t count, void *obj);
LVectorIter  lvector_insert_seg     (LVectorIter iter, void *first, void *last);
LVectorIter  lvector_emplace        (LVectorIter iter, void *args);
LVectorIter  lvector_erase          (LVectorIter iter);
LVectorIter  lvector_erase_seg      (LVectorIter first, LVectorIter last);
void         lvector_push_back      (LVector *self, void *obj);
void         lvector_emplace_back   (LVector *self, void *args);
void         lvector_pop_back       (LVector *self);
void         lvector_resize         (LVector *self, size_t count, void *args);
void         lvector_swap           (LVector *self, LVector *dest);

// Functions of LVector Iterator.
void        *lvector_iter_next      (void *self);
void        *lvector_iter_prev      (void *self);
void        *lvector_iter_forward   (void *self, size_t offset);
void        *lvector_iter_back      (void *self, size_t offset);
void        *lvector_iter_add       (void *self, size_t offset);
void        *lvector_iter_minus     (void *self, size_t offset);

ptrdiff_t    lvector_iter_dist                (void *self, void *dest);
bool         lvector_iter_is_less             (void *self, void *dest);
bool         lvector_iter_is_less_or_equal    (void *self, void *dest);
bool         lvector_iter_is_greater          (void *self, void *dest);
bool         lvector_iter_is_greater_or_equal (void *self, void *dest);
bool         lvector_iter_is_equal            (void *self, void *dest);

// Error numbers.
#define LVEC_OK                 (unsigned)0x00000000    // No error has occured.
    // Errors in function lvector_init.
#define LVEC_INIT_PRIV_ERR      (unsigned)0x00010001    // Allocating memory failed for res->__priv.
#define LVEC_INIT_ARG_ERR       (unsigned)0x00010002    // args == NULL.
#define LVEC_INIT_AT_ERR        (unsigned)0x00010003    // Allocating memory failed for res->__priv->_at.
    // Errors in function lvector_reserve.
#define LVEC_RSRV_AT_ERR        (unsigned)0x00020001    // Allocating memory failed for new_at.
    // Errors in function lvector_shrink_to_fit.
#define LVEC_SHRK_SIZE_ERR      (unsigned)0x00030001    // size of the lvector object bigger than capacity.
#define LVEC_SHRK_AT_ERR        (unsigned)0x00030002    // Allocating memory failed for new_at.


extern const LVectorOps LVector_ops;
extern const RandomAccessIterOps LVector_iter_ops;

#define LVector_INIT_ARGS_DEFAULT     \
    .capacity = 10, .elem_init = NULL, .elem_free = NULL

#endif