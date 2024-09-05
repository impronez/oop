#include "Dictionary.h"

char CharToLowerCase(char ch)
{
    switch (ch)
    {
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
    case '�': ch = '�'; break;
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
        std::cout << "������ �������� ��������� ����� (�������) ��� ������. "
            << "��������� �� ���������.\n";
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
    std::cout << "����������� ����� \"" << key
        << "\". ������� ������� ��� ������ ������ ��� ������.\n";
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
        std::cout << "����� \"" << key
            << "\" ��������� � ������� ��� \"" << value << "\".\n";
    }
    else
    {
        std::cout << "����� \"" << key << "\" ���������������.\n";
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