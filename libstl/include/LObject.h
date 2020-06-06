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

/*****************************************************/

// #define __VOPS_OBJ__(Type) Type ## _ops
// #define __VOPS_ITER_OBJ__(Type) Type ## _iter_ops

// #define __INIT_ARGS_TYPE__(Type) Type ## InitArgs
// #define __INIT_ARGS_DEFAULT__(Type) Type ## _INIT_ARGS_DEFAULT
// #define __EAT_COMMA__(...)  , ## __VA_ARGS__
// #define __INIT_ARGS_SET__(Type, ElemType, ...)      \
//     (__INIT_ARGS_TYPE__(Type)){                     \
//         __INIT_ARGS_DEFAULT__(Type),                \
//         .elem_size = sizeof(ElemType)               \
//         __EAT_COMMA__(__VA_ARGS__)                  \
//     }
// #define __INIT_FUNC__(Type) __VOPS_OBJ__(Type).init

/*
 * The macro __NEW_OBJ__ will not work.
 * Cause __INIT_FUNC__ expects a null pointer (void *), but received a
 * specified type.
*/

// #define __LEFT_BRACKET__ (
// #define __NEW_OBJ__(Type, ElemType, ...)          \
//     (Type *)__INIT_FUNC__(Type)(__INIT_ARGS_SET__(Type, ElemType, __VA_ARGS__))

#endif