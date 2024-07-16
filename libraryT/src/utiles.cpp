#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cstring>

#define FLOAT_NAN std::numeric_limits<float>::quiet_NaN()
#define FLOAT_MIN std::numeric_limits<float>::min()
#define FLOAT_MAX std::numeric_limits<float>::max()

#define PRECISION 1E-8

#define CHECK_SQRT(x)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        if (x < 0)                                                                                                     \
        {                                                                                                              \
            return FLOAT_NAN;                                                                                          \
        }                                                                                                              \
        else if (x == 0)                                                                                               \
        {                                                                                                              \
            return 0;                                                                                                  \
        }                                                                                                              \
    } while (0)

inline float newtonSqrt(float x)
{
    CHECK_SQRT(x);

    float avg = x;
    float lastAvg = FLOAT_MAX;
    while (fabs(avg - lastAvg) > PRECISION)
    {
        lastAvg = avg;
        avg = (avg + x / avg) / 2;
    }
    return avg;
}

inline float binarySqrt(float x)
{
    CHECK_SQRT(x);

    float low = 0;
    float high = x;
    float mid = FLOAT_MAX;
    float lastMid = FLOAT_MIN;
    while (fabs(mid - lastMid) > PRECISION)
    {
        lastMid = mid;
        mid = (low + high) / 2;
        float midSquare = mid * mid;
        if (midSquare > x)
        {
            high = mid;
        }
        else if (midSquare < x)
        {
            low = mid;
        }
    }
    return mid;
}

inline float quickSqrt(float value)
{
    const float halfValue = 0.5f * value;
    int bits = 0;
    memcpy(&bits, &value, sizeof(int));
    bits = 0x5f375a86 - (bits >> 1);
    float guess = 0.0f;
    memcpy(&guess, &bits, sizeof(float));
    return 1 / (guess * (1.5f - halfValue * guess * guess));
}

namespace libraryT
{
namespace utiles
{
int Math::add(int x, int y)
{
    return x + y;
}

double Math::distance(const Point& p1, const Point& p2)
{
    return ::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int Math::sum(std::vector<int>& nums)
{
    int sum = 0;
    for (auto num : nums)
    {
        sum += num;
    }
    return sum;
}

size_t Math::hash(double x, PrintCallback callback, void *data)
{
    size_t res = std::hash<double>()(x);
    if (callback)
    {
        int tmp = callback("Callback", data);
        (void)tmp;
    }
    return res;
}

float Math::sqrt(float x)
{
    switch (m_method)
    {
        case SqrtMethod::Newton :
            return newtonSqrt(x);
        case SqrtMethod::Binary :
            return binarySqrt(x);
        default :
            return quickSqrt(x);
    }
}
} // namespace utiles
} // namespace libraryT

int MathAdd(int x, int y)
{
    return libraryT::utiles::Math::add(x, y);
}

double MathDistance(libraryT::utiles::Point p1, libraryT::utiles::Point p2)
{
    return libraryT::utiles::Math::distance(p1, p2);
}

int MathSum(int *arr, int size)
{
    std::vector<int> vec(arr, arr + size);
    return libraryT::utiles::Math::sum(vec);
}

size_t MathHash(double x, libraryT::utiles::PrintCallback callback, void *data)
{
    return libraryT::utiles::Math::hash(x, callback, data);
}

float MathSqrt(float x, int method)
{
    auto mathCls = libraryT::utiles::Math(static_cast<libraryT::utiles::SqrtMethod>(method));
    return mathCls.sqrt(x);
}