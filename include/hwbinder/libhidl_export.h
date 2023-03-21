#pragma once

#if defined(WIN32) || defined(_MSC_VER)

#if defined(LIBHIDL_IMPLEMENTATION)
#define LIBHIDL_EXPORT __declspec(dllexport)
#else
#define LIBHIDL_EXPORT __declspec(dllimport)
#endif  // defined(LIBHIDL_IMPLEMENTATION)

#else  // defined(WIN32)
#if defined(LIBHIDL_IMPLEMENTATION)
#define LIBHIDL_EXPORT __attribute__((visibility("default")))
#else
#define LIBHIDL_EXPORT
#endif  // defined(LIBHIDL_IMPLEMENTATION)
#endif

#ifdef _WIN32
#ifdef interface
#undef interface
#endif
#endif
