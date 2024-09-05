#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <bitset>

const int MIN_KEY = 0;
const int MAX_KEY = 255;
const std::string CRYPT = "crypt";
const std::string DECRYPT = "decrypt";

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string mode;
    int key;
};

bool IsNumber(const std::string& s)
{
    return (strspn(s.c_str(), "0123456789") == s.size());
}

bool IsCorrectKey(const int& key)
{
    if (key < MIN_KEY || key > MAX_KEY)
    {
        return false;
    }
    return true;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Invalid argument count.\n"
            << "Usage: crypt.exe <crypt|decrypt> <input file> <output file> <key> .\n";
        return std::nullopt;
    }

    std::string mode = argv[1];
    if (mode != CRYPT && mode != DECRYPT)
    {
        std::cout << "Incorrect mode: '" << argv[1] << ".'\n"
            << "Acceptable modes: 'crypt' | 'decrypt'.\n";
        return std::nullopt;
    }

    bool isCorrectValue = IsNumber(argv[4]);
    if (isCorrectValue)
    {
        isCorrectValue = IsCorrectKey(std::stoi(argv[4]));
    }
    if (!isCorrectValue)
    {
        std::cout << "Incorrect value of key: '" << argv[4] << "'.\n"
            << "Key is a number in the range [0; 255].\n";
        return std::nullopt;
    }
    int key = std::stoi(argv[4]);

    Args args;
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    args.key = key;
    args.mode = mode;
    return args;
}

int ManipulationBits(const int& code, bool& isEncryption)
{
    int result;
    if (isEncryption)
    {
        int firstPart = (code & 0b00000111) << 2;
        int secondPart = (code & 0b00011000) << 3;
        int thirdPart = (code & 0b01100000) >> 5;
        int fourthPart = (code & 0b10000000) >> 2;
        result = (firstPart | secondPart | thirdPart | fourthPart);
    }
    else
    {
        int firstPart = (code & 0b00000011) << 5;
        int secondPart = (code & 0b00011100) >> 2;
        int thirdPart = (code & 0b00100000) << 2;
        int fourthPart = (code & 0b11000000) >> 3;
        result = (firstPart | secondPart | thirdPart | fourthPart);
    }
    return result;
}

void TransformationFileDataIntoNewFile(std::istream& input, std::ostream& output,
    const int& key, bool& isEncryption)
{
    char ch;
    input.seekg(0, std::ios::beg);
    while (input.read(&ch, sizeof(ch)))
    {
        int crypt = static_cast<int>(ch);
        if (isEncryption)
        {
            crypt = crypt ^ key;
        }
        int result = ManipulationBits(crypt, isEncryption);
        if (!isEncryption)
        {
            result = result ^ key;
        }
        char newCh = (char)result;
        output.write(&newCh, sizeof(newCh));
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return -1;
    }

    std::ifstream inputFile(args->inputFileName, std::ios::in | std::ios::binary);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading.\n";
        return false;
    }

    std::ofstream outputFile(args->outputFileName, std::ios::out | std::ios::binary);
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open '" << args->outputFileName << "' for writing.\n";
        return false;
    }

    int key = args->key;
    bool isEncryption = true;
    if (args->mode == DECRYPT)
    {
        isEncryption = false;
    }
    TransformationFileDataIntoNewFile(inputFile, outputFile, key, isEncryption);
}
