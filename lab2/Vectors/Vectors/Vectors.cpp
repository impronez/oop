#include "Vectors.h"

std::vector<double> ReadData(std::istream& input, bool& isCorrectData)
{
    isCorrectData = true;
    std::vector<double> array;
    double num;
    while (!input.eof())
    {
        if (input >> num)
        {
            array.push_back(num);
        }
        else if (input.eof())
        {
            break;
        }
        else
        {
            std::cout << "Incorrect value!\n";
            isCorrectData = false;
            break;
        }
    }
    return array;
}

void MultiplicationEachElementOnMinElement(std::vector<double>& numbers)
{
    if (numbers.size() == 0)
    {
        return;
    }

    double minNum = *std::min_element(numbers.begin(), numbers.end());

    for (int i = 0; i < numbers.size(); i++)
    {
        numbers.at(i) *= minNum;
    }
}