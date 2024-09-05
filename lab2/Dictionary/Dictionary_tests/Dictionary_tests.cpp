#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include "../Dictionary/Dictionary.h"

SCENARIO("Checking the reading data")
{
	WHEN("Input file is an empty")
	{
		std::istringstream input("");
		Dictionary dict = ReadDataFromFile(input);
		THEN("Dictionary is also empty")
		{
			REQUIRE(dict.empty());
		}
	}

	WHEN("Input file have one key-value")
	{
		std::istringstream input("cat|���");
		Dictionary dict = ReadDataFromFile(input);
		THEN("Dictionary have 1 key-value")
		{
			REQUIRE(dict.size() == 1);
		}
	}

	WHEN("Input file have two key-value")
	{
		std::istringstream input("cat|���\nmeat|����");
		Dictionary dict = ReadDataFromFile(input);
		THEN("Dictionary have 2 key-value")
		{
			REQUIRE(dict.size() == 2);
		}
	}
}

SCENARIO("Translation searching")
{
	std::vector<std::string> firstTranslation{ "���" }, secondTranslation{ "����" };
	Dictionary dict{ { "cat", firstTranslation }, { "meat", secondTranslation} };
	WHEN("Search by key")
	{
		std::string key = "meat";
		Dictionary::iterator it = TranslationSearch(dict, key, false);
		THEN("Iterator key points to meat")
		{
			REQUIRE(it->first == key);
		}
	}

	WHEN("Search by value")
	{
		std::string key = "����";
		Dictionary::iterator it = TranslationSearch(dict, key, true);
		THEN("Iterator key points to meat")
		{
			REQUIRE(it->second.at(0) == key);
		}
	}

	WHEN("Non-existent word search")
	{
		std::string key = "cow";
		Dictionary::iterator it = TranslationSearch(dict, key, false);
		THEN("Iterator key points to end of dictionary")
		{
			REQUIRE(it == dict.end());
		}
	}
}

SCENARIO("Translation")
{
	std::vector<std::string> translation{ "���" };
	Dictionary dict{ { "cat", translation } };

	WHEN("Translation by key")
	{
		Dictionary::iterator it = dict.begin();
		THEN("Output string = '���' ")
		{
			REQUIRE(TranslateWord(it, false) == "���");
		}
	}

	WHEN("Translation by value")
	{
		Dictionary::iterator it = dict.begin();
		THEN("Output string = 'cat'")
		{
			REQUIRE(TranslateWord(it, true) == "cat");
		}
	}
}

SCENARIO("Key in different case")
{
	std::vector<std::string> translation{ "���", "�����"};
	Dictionary dict{ { "cat", translation } };
	WHEN("Key in different case")
	{
		std::string key = "CaT";
		Dictionary::iterator it = TranslationSearch(dict, key, false);
		THEN("Return a correct translation")
		{
			REQUIRE(TranslateWord(it, false) == "���, �����");
		}
	}

	WHEN("Value in different case")
	{
		std::string key = "�����";
		Dictionary::iterator it = TranslationSearch(dict, key, true);
		THEN("Return a correct translation")
		{
			REQUIRE(TranslateWord(it, true) == "cat");
		}
	}
}