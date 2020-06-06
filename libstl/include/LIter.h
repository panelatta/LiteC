#ifndef LITEC_LIBSTL_LITER_H
#define LITEC_LIBSTL_LITER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _RandomAccessIterOps RandomAccessIterOps;

struct _RandomAccessIterOps {
    void *(*next)(void *self);
    void *(*prev)(void *self);
    void *(*forward)(void *self, size_t offset);
    void *(*back)(void *self, size_t offset);
    void *(*add)(void *self, size_t offset);
    void *(*minus)(void *self, size_t offset);
    
    ptrdiff_t (*dist)(void *self, void *dest);
    bool (*is_less)(void *self, void *dest);
    bool (*is_less_or_equal)(void *self, void *dest);
    bool (*is_greater)(void *self, void *dest);
    bool (*is_greater_or_equal)(void *self, void *dest);
    bool (*is_equal)(void *self, void *dest);
};

#endif