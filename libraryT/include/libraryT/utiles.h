#pragma once

#ifndef LIBRARY_T_UTILES_H
#define LIBRARY_T_UTILES_H

#include <libraryT/common.h>

#include <vector>
#include <functional>
#include <cstddef>

namespace libraryT
{
namespace utiles
{
/**
 * @brief 开方方法的枚举
 */
enum class SqrtMethod
{
    Quick,  ///< 快速方法
    Newton, ///< 牛顿迭代法
    Binary  ///< 二分法
};

/**
 * @brief 二维坐标
 */
struct Point
{
    double x; ///< x坐标
    double y; ///< y坐标
};

/**
 * @brief 打印回调函数
 * @param 打印文字
 * @param 透传指针
 * @return 返回是否成功，0表示成功
 */
using PrintCallback = std::function<int(const char *, void *)>;

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

    /**
     * @brief 计算两个点间的距离
     * @param p1 第一个点
     * @param p2 第二个点
     * @return 返回两个点间的距离
     */
    static double distance(const Point& p1, const Point& p2);

    /**
     * @brief 计算一个数组的和
     * @param nums 数组
     * @return 返回数组的和
     */
    static int sum(std::vector<int>& nums);

#ifdef SWIG
    /**
     * @brief 获取一个数的哈希值
     * @param x 要计算哈希值的数
     * @param callback 打印回调函数
     * @return 返回开方结果
     */
#else
    /**
     * @brief 获取一个数的哈希值
     * @param x 要计算哈希值的数
     * @param callback 打印回调函数
     * @param data 透传指针
     * @return 返回开方结果
     */
#endif // SWIG
    static size_t hash(double x, PrintCallback callback, void *data);

    /**
     * @brief 构造函数
     * @param method 开方的方法
     */
    Math(SqrtMethod method = SqrtMethod::Quick) : m_method(method) { }

    /**
     * @brief 默认析构函数
     */
    ~Math() = default;

    /**
     * @brief 计算一个数的开方
     * @param x 开方数
     * @return 返回开方结果
     */
    float sqrt(float x);

private:
    SqrtMethod m_method; ///< 开方的方法
};
} // namespace utiles
} // namespace libraryT

#endif // LIBRARY_T_UTILES_H
