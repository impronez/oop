#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../CMyArray/CMyArray.hpp"

TEST_CASE("Create array")
{
	GIVEN("Array of double")
	{
		WHEN("Empty array")
		{
			CMyArray<double> array;
			REQUIRE(array.GetSize() == 0);
			REQUIRE(array.GetCapacity() == 0);
		}

		WHEN("With size")
		{
			CMyArray<double> array(5);
			REQUIRE(array.GetSize() == 5);
			REQUIRE(array.GetCapacity() == 5);
		}

		WHEN("With initialise list")
		{
			CMyArray<double> array{ 1,2,3,4,5 };
			REQUIRE(array.GetSize() == 5);
			REQUIRE(array.GetCapacity() == 5);
		}
	}

	GIVEN("Array of string")
	{
		WHEN("Empty array")
		{
			CMyArray<std::string> array;
			REQUIRE(array.GetSize() == 0);
			REQUIRE(array.GetCapacity() == 0);
		}

		WHEN("With size")
		{
			CMyArray<std::string> array(5);
			REQUIRE(array.GetSize() == 5);
			REQUIRE(array.GetCapacity() == 5);
		}

		WHEN("With initialise list")
		{
			CMyArray<std::string> array{ "lol", "kek" };
			REQUIRE(array.GetSize() == 2);
			REQUIRE(array.GetCapacity() == 2);
		}
	}

	GIVEN("Check of default value")
	{
		CMyArray<double> array(1);

		REQUIRE(array.GetSize() == 1);
		REQUIRE(array.GetCapacity() == 1);
		REQUIRE(*array.begin() == 0);
	}

	GIVEN("Check of default value")
	{
		CMyArray<std::string> array(1);

		REQUIRE(array.GetSize() == 1);
		REQUIRE(array.GetCapacity() == 1);
		REQUIRE(*array.begin() == "");
	}
}

