#include <libraryT/utiles.h>

#include <Poco/Path.h>

#include <iostream>
#include <string>

namespace libraryT
{
namespace utiles
{
int Math::add(int x, int y)
{
    std::string path = Poco::Path::self();
    int result = x + y;
    std::cout << "[" << path << "]: " << x << " + " << y << " = " << result << std::endl;
    return result;
}
} // namespace utiles
} // namespace libraryT

int MathAdd(int x, int y)
{
    return libraryT::utiles::Math::add(x, y);
}