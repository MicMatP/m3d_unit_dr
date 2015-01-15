
#ifndef M3D_DRIVER_LIB_EXPORT_H
#define M3D_DRIVER_LIB_EXPORT_H

#ifdef M3D_DRIVER_LIB_STATIC_DEFINE
#  define M3D_DRIVER_LIB_EXPORT
#  define M3D_DRIVER_LIB_NO_EXPORT
#else
#  ifndef M3D_DRIVER_LIB_EXPORT
#    ifdef m3d_driver_lib_EXPORTS
        /* We are building this library */
#      define M3D_DRIVER_LIB_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define M3D_DRIVER_LIB_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef M3D_DRIVER_LIB_NO_EXPORT
#    define M3D_DRIVER_LIB_NO_EXPORT 
#  endif
#endif

#ifndef M3D_DRIVER_LIB_DEPRECATED
#  define M3D_DRIVER_LIB_DEPRECATED __declspec(deprecated)
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
