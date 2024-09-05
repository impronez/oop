#include "Dictionary.h"

char CharToLowerCase(char ch)
{
    switch (ch)
    {
    case 'А': ch = 'а'; break;
    case 'Б': ch = 'б'; break;
    case 'В': ch = 'в'; break;
    case 'Г': ch = 'г'; break;
    case 'Д': ch = 'д'; break;
    case 'Е': ch = 'е'; break;
    case 'Ж': ch = 'ж'; break;
    case 'З': ch = 'з'; break;
    case 'И': ch = 'и'; break;
    case 'Й': ch = 'й'; break;
    case 'К': ch = 'к'; break;
    case 'Л': ch = 'л'; break;
    case 'М': ch = 'м'; break;
    case 'Н': ch = 'н'; break;
    case 'О': ch = 'о'; break;
    case 'П': ch = 'п'; break;
    case 'Р': ch = 'р'; break;
    case 'С': ch = 'с'; break;
    case 'Т': ch = 'т'; break;
    case 'У': ch = 'у'; break;
    case 'Ф': ch = 'ф'; break;
    case 'Х': ch = 'х'; break;
    case 'Ц': ch = 'ц'; break;
    case 'Ч': ch = 'ч'; break;
    case 'Ш': ch = 'ш'; break;
    case 'Щ': ch = 'щ'; break;
    case 'Ъ': ch = 'ъ'; break;
    case 'Ы': ch = 'ы'; break;
    case 'Ь': ch = 'ь'; break;
    case 'Э': ch = 'э'; break;
    case 'Ю': ch = 'ю'; break;
    case 'Я': ch = 'я'; break;
    default: ch = tolower(ch);
    }
    return (ch);
}

Dictionary ReadDataFromFile(std::istream& file)
{
    Dictionary dict;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        size_t startPos = 0;
        std::vector<std::string> values;
        std::string key;
        std::string value;

        size_t endPos = line.find("|", startPos);
        key = line.substr(startPos, endPos);
        startPos = endPos + 1; // because std::string.find() - [x;y)
        while (startPos < line.length())
        {
            endPos = line.find("|", startPos);
            if (endPos == std::string::npos)
            {
                value = line.substr(startPos);
                values.push_back(value);
                break;
            }
            value = line.substr(startPos, endPos - startPos);
            startPos = endPos + 1; // without '|'
            values.push_back(value);
        }
        dict[key] = values;
    }
    return dict;
}

std::string StringToLowerCase(std::string str)
{
    for (auto& ch : str)
    {
        ch = CharToLowerCase(ch);
    }
    return str;
}

void DictionarySaving(Dictionary& dict, char* outputFileName)
{
    std::ofstream output(outputFileName);
    if (!output.is_open())
    {
        std::cout << "Ошибка открытия выходного файла (словаря) для записи. "
            << "Изменения не сохранены.\n";
        return;
    }
    Dictionary::iterator it = dict.begin();
    for (int i = 0; it != dict.end(); it++, i++)
    {
        output << it->first;

        for (int y = 0; y < it->second.size(); y++)
        {
            output << "|" << it->second.at(y);
        }

        output << std::endl;
    }
}

std::string TranslateWord(Dictionary::iterator& it, bool isValue)
{
    std::string translated;
    if (!isValue)
    {
        if (it->second.size() == 1)
        {
            translated.append(it->second.front());
        }
        else
        {
            for (int i = 0; i < it->second.size(); i++)
            {
                if (i != 0)
                {
                    translated.append(", ");
                }
                translated.append(it->second.at(i));
            }
        }
    }
    else
    {
        translated.append(it->first);
    }
    return translated;
}

Dictionary::iterator TranslationSearch(Dictionary& dict, std::string key, bool searchByValue)
{
    Dictionary::iterator it = dict.begin();
    bool found = false;
    std::string lowerKey = StringToLowerCase(key);
    while (it != dict.end())
    {
        std::string lowerFindKey;
        if (!searchByValue)
        {
            lowerFindKey = StringToLowerCase(it->first);
            if (lowerKey == lowerFindKey)
            {
                found = true;
            }
        }
        else
        {
            for (int i = 0; i < it->second.size(); i++)
            {
                lowerFindKey = StringToLowerCase(it->second.at(i));
                if (lowerKey == lowerFindKey)
                {
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            break;
        }
        it++;
    }
    return it;
}

bool IsRussianSymbols(const std::string& str)
{
    int code = static_cast<unsigned char>(str[0]);
    if (code >= 192 && code <= 255)
    {
        return true;
    }
    return false;
}

void AddWordToDictionary(Dictionary& dict, std::string& key, bool isValue)
{
    std::cout << "Неизвестное слово \"" << key
        << "\". Введите перевод или пустую строку для отказа.\n";
    std::string value;
    std::getline(std::cin, value);
    if (!value.empty())
    {
        if (!isValue)
        {
            dict[key] = std::vector<std::string>{ value };
        }
        else
        {
            dict[value].push_back(key);
        }
        std::cout << "Слово \"" << key
            << "\" сохранено в словаре как \"" << value << "\".\n";
    }
    else
    {
        std::cout << "Слово \"" << key << "\" проигнорировано.\n";
    }
}

size_t TranslatedWordsCount(Dictionary& dict)
{
    size_t count = 0;
    Dictionary::iterator it = dict.begin();
    while (it != dict.end())
    {
        count += it->second.size();
        it++;
    }
    return count;
}