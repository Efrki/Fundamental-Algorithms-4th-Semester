#include <iostream>
#include "../include/array.hpp"


using namespace my_container;


int main(int argc, char *argv[])
{

    (void)argc; (void)argv;

    Array<int, 5> arr{1,2,3,4,5};

    for (auto i = arr.cbegin(); i != arr.cend(); i++)
    {
        std::cout << *i << " ";
        
    }
    std::cout << std::endl;
    for (auto i = arr.begin(); i != arr.end(); i++)
    {
        std::cout << *i << " ";
        
    }
    std::cout << std::endl;
    for (auto i = arr.crbegin(); i != arr.crend(); i++)
    {
        std::cout << *i << " ";
        
    }
    std::cout << std::endl;
    for (auto i = arr.rbegin(); i != arr.rend(); i++)
    {
        std::cout << *i << " ";
        
    }
    std::cout << std::endl;
    return 0;
}