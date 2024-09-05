#include "Dictionary.h"

void Exit(Dictionary& dict, size_t const& size, char* outputFileName)
{
    std::string str;
    
    if (TranslatedWordsCount(dict) != size)
    {
        std::cout << "В словарь были внесены изменения. " <<
            "Введите Y или y для сохранения перед выходом.\n";
        std::getline(std::cin, str);
        if (!str.empty() && (str == "y" || str == "Y"))
        {
            DictionarySaving(dict, outputFileName);
            std::cout << "Изменения сохранены. Доброго здравия!\n";
        }
        else {
            std::cout << "Изменения не сохранены. Всего хорошего.\n";
        }
    }
    else
    {
        std::cout << "До свидания!\n";
    }
}

void Menu(Dictionary& dict)
{
    std::string key;
    Dictionary::iterator it;
    while (!std::cin.eof())
    {
        std::getline(std::cin, key);

        if (key.empty())
        {
            continue;
        }

        if (key == "...")
        {
            break;
        }

        bool searchByValue = IsRussianSymbols(key);

        it = TranslationSearch(dict, key, searchByValue);
        
        if (it == dict.end())
        {
            AddWordToDictionary(dict, key, searchByValue);
        }
        else
        {
            std::cout << TranslateWord(it, searchByValue) << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream input(argv[1]);
    Dictionary dictionary;
    if (input.is_open())
    {
        dictionary = ReadDataFromFile(input);
        input.close();
    }
    size_t dictionarySize = TranslatedWordsCount(dictionary);
    Menu(dictionary);
    Exit(dictionary, dictionarySize, argv[1]);
}