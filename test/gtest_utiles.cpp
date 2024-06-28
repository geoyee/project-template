#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <gtest/gtest.h>

TEST(libraryT_utiles_test, add_capi)
{
    libraryT::utiles::Math mathT;
    EXPECT_EQ(mathT.add(1, 2), 3);
}

TEST(libraryT_utiles_test, add_memfunc)
{
    EXPECT_EQ(MathAdd(1, 2), 3);
}