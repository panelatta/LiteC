#include "../include/LVector.h"
#include <string.h>

// The instantiated object of the vtable class LVectorOps.
const LVectorOps LVector_ops = {
    .init = lvector_init,
    .free = lvector_free,
    .at = lvector_at,
    .front = lvector_front,
    .back = lvector_back,
    .data = lvector_data,
    .get_iter = lvector_get_iter,
    .begin = lvector_begin,
    .end = lvector_end,
    .rbegin = lvector_rbegin,
    .rend = lvector_rend,
    .empty = lvector_empty,
    .size = lvector_size,
    .elem_size = lvector_elem_size,
    .capacity = lvector_capacity,
    .reserve = lvector_reserve,
    .shrink_to_fit = lvector_shrink_to_fit,
    .clear = lvector_clear,
    .insert = lvector_insert,
    .insert_seg = lvector_insert_seg,
    .emplace = lvector_emplace,
    .erase = lvector_erase,
    .erase_seg = lvector_erase_seg,
    .push_back = lvector_push_back,
    .emplace_back = lvector_emplace_back,
    .pop_back = lvector_pop_back,
    .resize = lvector_resize,
    .swap = lvector_swap
};

// An instantiated object of the vtable class RandomAccessIterOps.
const RandomAccessIterOps LVector_iter_ops = {
    .next = lvector_iter_next,
    .prev = lvector_iter_prev,
    .forward = lvector_iter_forward,
    .back = lvector_iter_back,
    .add = lvector_iter_add,
    .minus = lvector_iter_minus,
    .dist = lvector_iter_dist,
    .is_less = lvector_iter_is_less,
    .is_less_or_equal = lvector_iter_is_less_or_equal,
    .is_greater = lvector_iter_is_greater,
    .is_greater_or_equal = lvector_iter_is_greater_or_equal,
    .is_equal = lvector_iter_is_equal
};

/*
 * Name: lvector_init
 * Description: Return an LVector object.
 * Arguments:
 *  - void *args: An LVectorInitArgs object, with init args.
 * Return Value:
 *  - void *: A (void *) pointer to the generated LVector object. If create failed, return NULL.
 */
void *lvector_init(void *args) {
    LVectorInitArgs *_args = (LVectorInitArgs *)args;

    LVector *res = (LVector *)malloc(sizeof(LVector));
    if(!res) {
        return NULL;
    }

    res->__errno = LVEC_OK;
    res->__priv = (LVectorPrivMembers *)malloc(sizeof(LVectorPrivMembers));
    res->__vops = &LVector_ops;
    if(!res->__priv) {
        res->__errno = LVEC_INIT_PRIV_ERR;
        return (void *)res;
    }

    if(!_args) {
        res->__errno = LVEC_INIT_ARG_ERR;
        return (void *)res;
    }

    res->__priv->_size = 0;
    res->__priv->_elem_size = _args->elem_size;
    res->__priv->_capacity = _args->capacity;
    res->__priv->_elem_init = _args->elem_init;
    res->__priv->_elem_free = _args->elem_free;
    res->__priv->_at = malloc(res->__priv->_elem_size * res->__priv->_capacity);
    if(!res->__priv->_at) {
        res->__errno = LVEC_INIT_AT_ERR;
    }

    return (void *)res;
}

/*
 * Name: lvector_free
 * Description: Free an LVector object.
 * Arguments:
 *  - void *self: A (void *) pointer to the LVector object to be freed.
 * Return Value:
 *  - void
 */
void lvector_free(void *self) {
    if(!self) {
        return;
    }
    LVector *_self = (LVector *)self;

    if(_self->__priv->_elem_free) {
        size_t _size = lvector_size(self);
        for(size_t i = 0; i < _size; i++) {
            _self->__priv->_elem_free(lvector_at(_self, i));
        }
    }
    free(lvector_data(_self));
    free(_self->__priv);
    free(_self);
}

/*
 * Name: lvector_at
 * Description: Return a (void *) pointer to self->__priv->_at[pos].
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 *  - int pos: the array index.
 * Return Value:
 *  - void *: A (void *) pointer to the position. If failed, return NULL.
 */
inline void *lvector_at(LVector *self, size_t pos) {
    return (
        self ? 
        (
            pos < lvector_size(self) ?
            (void *)((char *)lvector_data(self) + pos * lvector_elem_size(self)) :
            NULL
        ) :
        NULL
    );
}

/*
 * Name: lvector_front
 * Description: 
 *  - Return a (void *) pointer to the first element.
 *  - In the C++ Standard, the function front() should return the value of the first element
 *  - but as C does not have generic types, we return a (void *) pointer instead.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - void *: A (void *) pointer to the first element. If failed, return NULL.
 */
inline void *lvector_front(LVector *self) {
    return (
        self ?
        self->__priv->_at :
        NULL
    );
}

/*
 * Name: lvector_back
 * Description: 
 *  - Return a (void *) pointer to the last element.
 *  - In the C++ Standard, the function back() should return the value of the last element
 *  - but as C does not have generic types, we return a (void *) pointer instead.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - void *: A (void *) pointer to the last element. If failed, return NULL.
 */
inline void *lvector_back(LVector *self) {
    return (
        self ?
        lvector_at(self, lvector_size(self) - 1) :
        NULL
    );
}

/*
 * Name: lvector_data
 * Description: 
 *  - Return a (void *) pointer to the first element.
 *  - As same as lvector_front() here.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - void *: A (void *) pointer to the first element. If failed, return NULL.
 */
inline void *lvector_data(LVector *self) {
    return (
        self ?
        self->__priv->_at :
        NULL
    );
}

/*
 * Name: lvector_get_iter
 * Description:
 *  - Return an LVectorIter object, which points to the specific position
 *  - of an LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 *  - int pos: The specific position.
 *  - bool is_reverse: The requested iterator is reverse or not.
 * Return Value:
 *  - LVectorIter: The requested LVectorIter object.
 */
inline LVectorIter lvector_get_iter(LVector *self, size_t pos, bool is_reverse) {
    LVectorIter res = {
        .__vops = &LVector_iter_ops,
        .elem_size = lvector_elem_size(self),
        .is_reverse = is_reverse,
        .at = lvector_at(self, pos)
    };
    return res;
}

/*
 * Name: lvector_begin
 * Description:
 *  - Return an LVectorIter object, which points to the first element
 *  - of the specific LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - LVectorIter: The requested LVectorIter object.
 */
inline LVectorIter lvector_begin(LVector *self) {
    return lvector_get_iter(self, 0, false);
}

/*
 * Name: lvector_end
 * Description:
 *  - Return an LVectorIter object, which points to the next position
 *  - of the last element of the specific LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - LVectorIter: The requested LVectorIter object.
 */
inline LVectorIter lvector_end(LVector *self) {
    return lvector_get_iter(self, lvector_size(self), false);
}

/*
 * Name: lvector_rbegin
 * Description:
 *  - Return an reverse LVectorIter object, which points to the first element
 *  - of the specific LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - LVectorIter: The requested reverse LVectorIter object.
 */
inline LVectorIter lvector_rbegin(LVector *self) {
    return lvector_get_iter(self, 0, true);
}

/*
 * Name: lvector_rend
 * Description:
 *  - Return an reverse LVectorIter object, which points to the next position
 *  - of the last element of the specific LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - LVectorIter: The requested reverse LVectorIter object.
 */
inline LVectorIter lvector_rend(LVector *self) {
    return lvector_get_iter(self, lvector_size(self), true);
}

/*
 * Name: lvector_empty
 * Description:
 *  - Return a bool value, which points out an LVector object is empty or not.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - bool: Return true or false when the LVector object is empty or not.
 */
inline bool lvector_empty(LVector *self) {
    return (bool)(lvector_size(self) == 0);
}

/*
 * Name: lvector_size
 * Description:
 *  - Return the available size of an LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - size_t: The available size of the LVector object.
 */
inline size_t lvector_size(LVector *self) {
    return self->__priv->_size;
}

/*
 * Name: lvector_elem_size
 * Description:
 *  - Return the size of the elements of an LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - size_t: The size of the elements of the LVector object.
 */
inline size_t lvector_elem_size(LVector *self) {
    return self->__priv->_elem_size;
}

/*
 * Name: lvector_capacity
 * Description:
 *  - Return the capacity of an LVector object.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - size_t: The capacity of the LVector object.
 */
inline size_t lvector_capacity(LVector *self) {
    return self->__priv->_capacity;
}

/*
 * Name: lvector_reserve
 * Description:
 *  - Enlarge the capacity of an LVector object to new_cap when the
 *  - capacity is less than new_cap.
 *  - When new_cap is less than the capacity, the function do nothing.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 *  - size_t new_cap: The new capacity.
 * Return Value:
 *  - void
 */
void lvector_reserve(LVector *self, size_t new_cap) {
    if(!self) {
        return;
    }
    if(new_cap > lvector_capacity(self)) {
        void *new_at = malloc(lvector_elem_size(self) * new_cap);
        if(!new_at) {
            self->__errno = LVEC_RSRV_AT_ERR;
            return;
        }
        self->__priv->_capacity = new_cap;
        memcpy(new_at, lvector_data(self), lvector_size(self) * lvector_elem_size(self));
        free(lvector_data(self));
        self->__priv->_at = new_at;
    }
}

/*
 * Name: lvector_shrink_to_fit
 * Description:
 *  - Request the removal of unused capacity.
 *  - It will reduce the LVector object's capacity to size.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - void
 */
void lvector_shrink_to_fit(LVector *self) {
    if(!self) {
        return;
    }

    size_t _size = lvector_size(self);
    size_t _capacity = lvector_capacity(self);
    if(_size == _capacity) {
        return;
    } else if(_size > _capacity) {
        self->__errno = LVEC_SHRK_SIZE_ERR;
        return;
    } else {
        void *new_at = malloc(lvector_elem_size(self) * _size);
        if(!new_at) {
            self->__errno = LVEC_SHRK_AT_ERR;
            return;
        }
        self->__priv->_capacity = _size;
        memcpy(new_at, lvector_data(self), lvector_elem_size(self) * _size);
        free(lvector_data(self));
        self->__priv->_at = new_at;
    }
}

/*
 * Name: lvector_clear
 * Description:
 *  - Clear all of the elements in the LVector object.
 *  - It will reduce the LVector object's size to 0, but won't influence capacity.
 *  - If _elem_size is not NULL, the function will call it for all of the elements,
 *  - or just simply reduce size to 0.
 * Argument:
 *  - LVector *self: A pointer to the LVector object.
 * Return Value:
 *  - void
 */
void lvector_clear(LVector *self) {
    if(!self) {
        return;
    }
    
    if(self->__priv->_elem_free) {
        size_t _size = lvector_size(self);
        for(size_t i = 0; i < _size; i++) {
            self->__priv->_elem_free(lvector_at(self, i));
        }
    }
    self->__priv->_size = 0;
}