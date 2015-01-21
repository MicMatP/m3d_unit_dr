
#ifndef M3D_DRIVER_LIB_EXPORT_H
#define M3D_DRIVER_LIB_EXPORT_H



#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(_GCC)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif


#ifdef M3D_DRIVER_LIB_STATIC_DEFINE
#  define M3D_DRIVER_LIB_EXPORT
#  define M3D_DRIVER_LIB_NO_EXPORT
#else
#  ifndef M3D_DRIVER_LIB_EXPORT
#    ifdef m3d_driver_lib_EXPORTS
        /* We are building this library */
#      define M3D_DRIVER_LIB_EXPORT EXPORT
#    else
        /* We are using this library */
#      define M3D_DRIVER_LIB_EXPORT IMPORT
#    endif
#  endif

#  ifndef M3D_DRIVER_LIB_NO_EXPORT
#    define M3D_DRIVER_LIB_NO_EXPORT 
#  endif
#endif

#ifndef M3D_DRIVER_LIB_DEPRECATED
#  define M3D_DRIVER_LIB_DEPRECATED EXPORT
#endif

#ifndef M3D_DRIVER_LIB_DEPRECATED_EXPORT
#  define M3D_DRIVER_LIB_DEPRECATED_EXPORT M3D_DRIVER_LIB_EXPORT M3D_DRIVER_LIB_DEPRECATED
#endif

#ifndef M3D_DRIVER_LIB_DEPRECATED_NO_EXPORT
#  define M3D_DRIVER_LIB_DEPRECATED_NO_EXPORT M3D_DRIVER_LIB_NO_EXPORT M3D_DRIVER_LIB_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define M3D_DRIVER_LIB_NO_DEPRECATED
#endif

#endif
