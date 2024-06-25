#pragma once

#ifndef LIBRARY_T_UTILES_H
#define LIBRARY_T_UTILES_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
#if defined(LIBRART_STATIC)
#define LIB_API
#elif defined(LIBRART_EXPORTS) // LIBRART_SHARED
#define LIB_API __declspec(dllimport)
#else
#define LIB_API __declspec(dllexport)
#endif // LIBRART_STATIC
#else
#define LIB_API
#endif // _MSC_VER || __CYGWIN__ || __MINGW32__ || __BCPLUSPLUS__ || __MWERKS__

namespace libraryT
{
namespace utiles
{
class LIB_API Math
{
public:
    static int add(int x, int y);
};
} // namespace utiles
} // namespace libraryT

extern "C"
{
    int LIB_API MathAdd(int x, int y);
}

#endif // LIBRARY_T_UTILES_H