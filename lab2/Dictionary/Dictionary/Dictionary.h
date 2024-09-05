#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <Windows.h>

typedef std::map<std::string, std::vector<std::string>> Dictionary;

std::string StringToLowerCase(std::string str);

void DictionarySaving(Dictionary& dict, char* outputFileName);

std::string TranslateWord(Dictionary::iterator& it, bool isValue);

Dictionary::iterator TranslationSearch(Dictionary& dict, std::string key, bool searchByValue);

bool IsRussianSymbols(const std::string& str);

void AddWordToDictionary(Dictionary& dict, std::string& key, bool isValue);

size_t TranslatedWordsCount(Dictionary& dict);

void Menu(Dictionary& dict);

Dictionary ReadDataFromFile(std::istream& file);