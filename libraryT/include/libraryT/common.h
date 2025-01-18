#pragma once

#ifndef LIBRARY_T_COMMON_H
#define LIBRARY_T_COMMON_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
#if defined(LIBRART_STATIC)
#define LIB_API
#elif defined(LIBRART_IMPORTS) // LIBRART_SHARED
#define LIB_API __declspec(dllimport)
#else
#define LIB_API __declspec(dllexport)
#endif // LIBRART_STATIC
#else
#if __GNUC__ >= 4
#define LIB_API __attribute__((visibility("default")))
#else
#define LIB_API
#endif // __GNUC__ >= 4
#endif // _MSC_VER || __CYGWIN__ || __MINGW32__ || __BCPLUSPLUS__ || __MWERKS__

#include <dbg.h>
#include <spdlog/spdlog.h>

#endif // LIBRARY_T_COMMON_H
