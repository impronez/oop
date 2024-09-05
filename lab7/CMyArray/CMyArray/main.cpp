#include <iostream>
#include <vector>
#include <string>
#include "CMyArray.hpp"

int main()
{
    CMyArray<int> array{1, 2, 3, 4, 5};
    for (int i = 0; i < array.GetSize(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    array.Push(6);
    for (int i = 0; i < array.GetSize(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    array.Push(7);
    for (int i = 0; i < array.GetSize(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    auto it = array.begin();
    std::cout << *it;

    std::cout << *it;
    //*/


    for (auto it = array.rbegin(); it != array.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    
}