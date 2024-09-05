#include "Vectors.h"

const int ACCURACY_OF_NUMBERS = 3;

void PrintContantsOfArray(std::vector<double>& numbers)
{
    if (numbers.size() == 0)
    {
        std::cout << "Empty array.\n";
        return;
    }

    for (int i = 0; i < numbers.size(); i++)
    {
        std::cout << std::setprecision(ACCURACY_OF_NUMBERS)
            << std::fixed << numbers.at(i) << " ";
    }
}

int main()
{
    std::cout << "Enter the numbers (end is '^Z'): \n";
    bool isCorrectData;
    std::vector<double> numbers = ReadData(std::cin, isCorrectData);

    if (!isCorrectData)
    {
        return -1;
    }
    
    if (numbers.size() > 0)
    {
        MultiplicationEachElementOnMinElement(numbers);
        std::sort(numbers.begin(), numbers.end());
    }

    PrintContantsOfArray(numbers);
}