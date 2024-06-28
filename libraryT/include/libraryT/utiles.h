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
/**
 * @brief 自定义的Math类
 */
class LIB_API Math
{
public:
    /**
     * @brief 计算两个整数的加法
     * @param x 第一个整数
     * @param y 第二个整数
     * @return 返回两个整数的和
     */
    static int add(int x, int y);
};
} // namespace utiles
} // namespace libraryT

#endif // LIBRARY_T_UTILES_H