#define CATCH_CONFIG_MAIN
#include "../PrimeNumbersGenerating/NumbersGenerator.h"
#include "../../../../catch/catch.hpp"


SCENARIO("Checking the upper bound number")
{
	WHEN("Num of upper bound is incorrect")
	{
		int num = ParseInt("asd");
		THEN("Num = -1")
		{
			REQUIRE(num == -1);
		}
	}

	WHEN("Num of upper bound is more than MAX")
	{
		int num = ParseInt("100000001");
		THEN("Num = -1")
		{
			REQUIRE(num == -1);
		}
	}

	WHEN("Num of upper bound is correct")
	{
		int num = ParseInt("100");
		THEN("Num is also correct")
		{
			REQUIRE(num == 100);
		}
	}
}

SCENARIO("Checking the prime numbers generator")
{
	WHEN("Num of upper bound is MAX")
	{
		int upperBound = MAX_NUM_OF_UPPER_BOUND;
		std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
		THEN("Size of set is 5761455")
		{
			REQUIRE(primeNums.size() == 5761455);
		}
	}

	WHEN("Num of upper bound is MIN")
	{
		int upperBound = 2;
		std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
		THEN("Size of set is 1")
		{
			REQUIRE(primeNums.size() == 1);
		}
	}
}
