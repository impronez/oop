#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include "../Vectors/Vectors.h"


SCENARIO("Read check")
{
	bool isCorrectData = true;
	WHEN("Input is empty")
	{
		std::istringstream input;
		std::vector<double> v = ReadData(input, isCorrectData);
		THEN("Output vector is also empty")
		{
			REQUIRE(v.empty());
		}
	}

	WHEN("Input is not empty and correct")
	{
		std::istringstream input("123 2");
		std::vector<double> v = ReadData(input, isCorrectData);
		THEN("Output vector is not empty")
		{
			REQUIRE(v.size() == 2);
		}
	}

	WHEN("Input is not empty and incorrect")
	{
		std::istringstream input("aaa");
		std::vector<double> v = ReadData(input, isCorrectData);
		THEN("Output vector is not empty")
		{
			REQUIRE(!isCorrectData);
		}
	}

	WHEN("Input is line by line")
	{
		std::istringstream input("213\n123\n2\n^Z");
		std::vector<double> v = ReadData(input, isCorrectData);
		THEN("Output vector is not empty")
		{
			REQUIRE(v.size() == 3);
		}
	}
}

SCENARIO("Empty vector return an empty vector")
{
	WHEN("Input vector is an empty")
	{
		std::vector<double> v = {};
		THEN("Output vector is also an empty")
		{
			MultiplicationEachElementOnMinElement(v);
			REQUIRE(v.empty());
		}
	}
}

SCENARIO("Multiplication nums of vector to min element")
{
	WHEN("Input vector is not empty")
	{
		std::vector<double> v{ 0.5, 1, 10, 20 };
		std::vector<double> result{ 0.25, 0.5, 5, 10 };
		THEN("Output vector is also not empty")
		{
			MultiplicationEachElementOnMinElement(v);
			REQUIRE(v == result);
		}
	}
}