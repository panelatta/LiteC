#ifndef LITEC_LIBSTL_LOBJECT_H
#define LITEC_LIBSTL_LOBJECT_H

// #define _LEFT_BRACKET_                          (
// #define _NEW_SELECT_HELPER_(_1, _2, _3, ...)    _3
// #define _MID_LAYER_(...)                        __VA_ARGS__
// #define _NEW_DEF_(Type, Val, ...)               Type ## _init(Val)
// #define _NEW_UNDEF_(Type, ...)                  Type ## _init(Type ## _defval)
// #define _NEW_(...)                              \
//     _MID_LAYER_(_NEW_SELECT_HELPER_(            \
//         __VA_ARGS__, _NEW_DEF_, _NEW_UNDEF_)(__VA_ARGS__))

#define __VOPS_OBJ__(__Type) __Type ## 

#endif