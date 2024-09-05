#include "NumbersGenerator.h"
#include <stdexcept>

const int MAX_NUM_OF_UPPER_BOUND = 100000000;

int ParseUpperBoundNum(const std::string& num)
{
    int upperBound;
    upperBound = std::stoi(num);
    if (upperBound < 0)
    {
        throw std::invalid_argument("Incorrect value of upper bound num.");
    }
    else if (upperBound > MAX_NUM_OF_UPPER_BOUND)
    {
        throw std::overflow_error("Input value of upper bound should be no more than.");
    }
    
    return upperBound;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNums;
    std::vector<bool> prime(upperBound + 1, true);

    for (int i = 2; i * i <= upperBound; i++)
    {
        if (prime[i])
        {
            for (int j = i * i; j <= upperBound; j += i)
            {
                prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; i++)
    {
        if (prime[i])
        {
            primeNums.insert(i);
        }
    }
    return primeNums;
}

