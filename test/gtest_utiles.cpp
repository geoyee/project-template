#include <libraryT/utiles.h>
#include <gtest/gtest.h>

TEST(libraryT_utiles_test, add)
{
    libraryT::utiles::Math mathT;
    EXPECT_EQ(mathT.add(1, 2), 3);
    EXPECT_EQ(MathAdd(1, 2), 3);
}