#ifndef GLOBAL_H
#define GLOBAL_H

// compiler definitions
#if defined(__GNUC__)
#define GCC_COMPILER
#endif
#if defined(_MSC_VER) || defined(_MSC_FULL_VER)
#define MSVC_COMPILER
#endif

// os definitions
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__TOS_WIN__) || defined(_WINDOWS_)
#define WINDOWS_OS
#endif
#if defined(linux) || defined(__linux)
#define LINUX_OS
#endif
#if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#define UNIX_OS
#endif

// std library
#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#define LIBSTDCPP
#endif

// includes
#if defined(WINDOWS_OS)
#include <windows.h>
#elif defined(LINUX_OS) || defined(UNIX_OS)
#include <unistd.h>
#endif

#endif // GLOBAL_H
