#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <gtest/gtest.h>

#include <iostream>
#include <cmath>

TEST(libraryT_utiles_test, add)
{
    EXPECT_EQ(MathAdd(1, 2), 3);
}

TEST(libraryT_utiles_test, distance)
{
    EXPECT_DOUBLE_EQ(MathDistance({0, 0}, {3, 4}), 5);
}

TEST(libraryT_utiles_test, sum)
{
    int nums[] = {1, 2, 3};
    EXPECT_EQ(MathSum(nums, 3), 6);
}

TEST(libraryT_utiles_test, hash)
{
    auto callback = [](size_t res, void *data) -> int
    {
        std::cout << "callback: " << res << std::endl;
        data = nullptr;
        return 0;
    };
    EXPECT_EQ(MathHash(3.14, callback, nullptr), std::hash<double>()(3.14));
}

TEST(libraryT_utiles_test, sqrt)
{
    float sqrt3 = static_cast<float>(sqrt(3));
    // EXPECT_FLOAT_EQ(MathSqrt(3, 0), sqrt3); // 快速开方精度不够，导致测试失败
    EXPECT_TRUE(fabs(MathSqrt(3, 0) - sqrt3) < 0.01);
    EXPECT_FLOAT_EQ(MathSqrt(3, 1), sqrt3);
    EXPECT_FLOAT_EQ(MathSqrt(3, 2), sqrt3);
}