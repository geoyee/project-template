#include <libraryT/utiles.h>
#include <libraryT/capi.h>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " int int" << std::endl;
        return 1;
    }
    libraryT::utiles::Math mathT;
    std::cout << mathT.add(atoi(argv[1]), atoi(argv[2])) << std::endl;
    return 0;
}