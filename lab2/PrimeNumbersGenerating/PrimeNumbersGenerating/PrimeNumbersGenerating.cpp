#include "NumbersGenerator.h"

void PrintPrimeNumbers(std::set<int>& primeNums)
{
    std::set<int>::iterator it;
    for (it = primeNums.begin(); it != primeNums.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

int main(int argc, char* argv[])
{
    int upperBound;
    try
    {
        upperBound = ParseUpperBoundNum(argv[1]);
    }
    catch (const std::exception& err)
    {
        std::cout << err.what() << std::endl;
        return -1;
    }
    
    std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
    PrintPrimeNumbers(primeNums);
}