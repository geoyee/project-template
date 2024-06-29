#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <iostream>
#include <string>

namespace libraryT
{
namespace utiles
{
int Math::add(int x, int y)
{
    return x + y;
}
} // namespace utiles
} // namespace libraryT

int MathAdd(int x, int y)
{
    return libraryT::utiles::Math::add(x, y);
}