#define __VOPS_OBJ__(Type) Type ## _ops
#define __VOPS_ITER_OBJ__(Type) Type ## _iter_ops

#define __INIT_ARGS_TYPE__(Type) Type ## InitArgs
#define __INIT_ARGS_DEFAULT__(Type) Type ## _INIT_ARGS_DEFAULT
#define __EAT_COMMA__(...)  , ## __VA_ARGS__
#define __INIT_ARGS_SET__(Type, ElemType, ...)      \
    (__INIT_ARGS_TYPE__(Type)){                     \
        __INIT_ARGS_DEFAULT__(Type),                \
        .elem_size = sizeof(ElemType)               \
        __EAT_COMMA__(__VA_ARGS__)                  \
    }
#define __INIT_FUNC__(Type) __VOPS_OBJ__(Type).init

#define __LEFT_BRACKET__ (
#define __NEW_OBJ__(Type, ElemType, ...)          \
    (Type *)__INIT_FUNC__(Type)(__INIT_ARGS_SET__(Type, ElemType, __VA_ARGS__))

#define LVector_INIT_ARGS_DEFAULT     \
    .capacity = 10, .elem_init = NULL, .elem_free = NULL

__NEW_OBJ__(LVector, int);