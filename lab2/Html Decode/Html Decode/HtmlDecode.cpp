#include "Decoder.h"

void ReadingAndOutputOfDecodedString()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::cout << StringProcessing(line) << std::endl;
    }
}

int main()
{
    ReadingAndOutputOfDecodedString();
}
