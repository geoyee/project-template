#include <libraryT/utils.h>
#include <libraryT/capi.h>
#include <libraryT/version.h>

#include <iostream>

int main(int argc, char *argv[])
{
    libraryT::version::display();

    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " int int" << std::endl;
        return 1;
    }
    libraryT::utils::Math mathT;
    std::cout << mathT.add(atoi(argv[1]), atoi(argv[2])) << std::endl;
    return 0;
}