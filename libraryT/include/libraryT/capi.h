#pragma once

#ifndef LIBRARY_T_CAPI_H
#define LIBRARY_T_CAPI_H

#include <libraryT/utiles.h>

extern "C"
{
    using namespace libraryT::utiles;

    /**
     * @brief 计算两个整数的加法
     * @param x 第一个整数
     * @param y 第二个整数
     * @return 返回两个整数的和
     */
    int LIB_API MathAdd(int x, int y);

    /**
     * @brief 计算两个点间的距离
     * @param p1 第一个点
     * @param p2 第二个点
     * @return 返回两个点间的距离
     */
    double LIB_API MathDistance(Point p1, Point p2);

#ifdef SWIG
    /**
     * @brief 计算一个数的和
     * @param arr 数组
     * @return 返回和
     */
#else
    /**
     * @brief 计算一个数的和
     * @param arr 数组
     * @param size 数的个数
     * @return 返回和
     */
#endif // SWIG
    int LIB_API MathSum(int *arr, int size);

#ifdef SWIG
    /**
     * @brief 计算一个数哈希值
     * @param x 需要计算的数
     * @param callback 打印回调函数
     * @return 返回哈希值
     */
#else
    /**
     * @brief 计算一个数哈希值
     * @param x 需要计算的数
     * @param callback 打印回调函数
     * @param data 透传指针
     * @return 返回哈希值
     */
#endif // SWIG
    size_t LIB_API MathHash(double x, PrintCallback callback, void *data);

    /**
     * @brief 计算一个数的开方
     * @param x 开方数
     * @param method 开方方法
     * @return 返回开方结果
     */
    float LIB_API MathSqrt(float x, int method);
}

#endif // LIBRARY_T_CAPI_H