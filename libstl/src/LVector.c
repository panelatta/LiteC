#include "../include/LVector.h"

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

void *lvector_init(void *args) {
    
}