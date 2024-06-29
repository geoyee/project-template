#pragma once

#ifndef LIBRARY_T_CAPI_H
#define LIBRARY_T_CAPI_H

#include <libraryT/utiles.h>

extern "C"
{
    /**
     * @brief 计算两个整数的加法
     * @param x 第一个整数
     * @param y 第二个整数
     * @return 返回两个整数的和
     */
    int LIB_API MathAdd(int x, int y);
}

#endif // LIBRARY_T_CAPI_H