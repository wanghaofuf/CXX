#ifndef __DESIGNPATTERNSLIBRARY__H___
#define __DESIGNPATTERNSLIBRARY__H___

#if  defined(_MSC_VER)
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)
#else
#define DLL_EXPORT 
#define DLL_IMPORT 
#endif

#ifndef DP_STATIC
#if  defined(_MSC_VER)
#  if defined(DP_BUILD_LIB)
#    define DP_EXPORT DLL_EXPORT
#  else
#    define DP_EXPORT DLL_IMPORT
#  endif
#else
#  define DP_EXPORT
#  endif
#else
#  define DP_EXPORT
#endif

#endif // __DESIGNPATTERNSLIBRARY__H___
