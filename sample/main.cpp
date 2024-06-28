#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <iostream>

int main(int argc, char *argv[])
{
    libraryT::utiles::Math mathT;
    std::cout << mathT.add(1, 2) << std::endl;
    std::cout << MathAdd(1, 2) << std::endl;
    return 0;
}