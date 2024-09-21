#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <dbg.h>
#include <gtest/gtest.h>

#include <iostream>
#include <cmath>

TEST(libraryT_utiles_test, add)
{
    auto res = dbg(MathAdd(1, 2));
    EXPECT_EQ(res, 3);
}

TEST(libraryT_utiles_test, distance)
{
    auto res = dbg(MathDistance({0, 0}, {3, 4}));
    EXPECT_EQ(res, 5);
}

TEST(libraryT_utiles_test, sum)
{
    int nums[] = {1, 2, 3};
    auto res = dbg(MathSum(nums, 3));
    EXPECT_EQ(res, 6);
}

TEST(libraryT_utiles_test, hash)
{
    auto callback = [](const char *res, void *data) -> int
    {
        std::cout << "Callback: " << res << std::endl;
        data = nullptr;
        return data == nullptr ? 0 : -1;
    };
    auto res = dbg(MathHash(3.14, callback, nullptr));
    EXPECT_EQ(res, std::hash<double>()(3.14));
}

TEST(libraryT_utiles_test, sqrt)
{
    float sqrt3 = dbg(static_cast<float>(sqrt(3)));
    auto res0 = dbg(MathSqrt(3, 0));
    auto res1 = dbg(MathSqrt(3, 1));
    auto res2 = dbg(MathSqrt(3, 2));
    EXPECT_TRUE(fabs(res0 - sqrt3) < 0.01); // 快速开方精度不够，导致测试失败
    EXPECT_FLOAT_EQ(res1, sqrt3);
    EXPECT_FLOAT_EQ(res2, sqrt3);
}
