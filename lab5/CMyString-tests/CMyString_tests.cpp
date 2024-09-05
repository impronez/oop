#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../CMyString/CMyString.h"
#include <sstream>

TEST_CASE("Creating CMyString object")
{
	GIVEN("Without parameters")
	{
		CMyString str;

		REQUIRE(str.GetLength() == 0);
		REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
	}

	GIVEN("With C-string parameter")
	{
		WHEN("Not empty C-string")
		{
			auto cStr = "test";
			CMyString str(cStr);

			REQUIRE(str.GetLength() == 4);
			REQUIRE(std::strcmp(str.GetStringData(), cStr) == 0);
		}

		WHEN("Empty C-string")
		{
			auto cStr = "";
			CMyString str(cStr);

			REQUIRE(str.GetLength() == 0);
			REQUIRE(std::strcmp(str.GetStringData(), cStr) == 0);
		}

		WHEN("Empty C-string")
		{
			CMyString str(nullptr);

			REQUIRE(str.GetLength() == 0);
			REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
		}
	}

	GIVEN("With C-string and length parameters")
	{
		WHEN("Empty C-string with null length")
		{
			auto cStr = "";
			CMyString str(cStr, 0);

			REQUIRE(str.GetLength() == 0);
			REQUIRE(std::strcmp(str.GetStringData(), cStr) == 0);
		}

		WHEN("C-string with shorter length")
		{
			auto cStr = "Hello, World!";
			CMyString str(cStr, 5);

			REQUIRE(str.GetLength() == 5);
			REQUIRE(std::strcmp(str.GetStringData(), "Hello") == 0);
		}

		WHEN("C-string with bigger length")
		{
			auto cStr = "Hello, World!";
			CMyString str(cStr, 15);

			REQUIRE(str.GetLength() == 15);
			REQUIRE(std::strcmp(str.GetStringData(), cStr) == 0);
		}

		WHEN("Empty C-string with bigger length")
		{
			auto cStr = "";
			CMyString str(cStr, 15);

			THEN("Length is 15")
			{
				REQUIRE(str.GetLength() == 15);
				REQUIRE(std::strcmp(str.GetStringData(), cStr) == 0);
			}
		}

		WHEN("Nullptr with bigger length")
		{
			CMyString str(nullptr, 15);

			THEN("Length is 0")
			{
				REQUIRE(str.GetLength() == 0);
				REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
			}
		}
	}

	GIVEN("With STL-string parameter")
	{
		WHEN("Empty stl-string")
		{
			std::string stlStr = "";

			CMyString str(stlStr);

			REQUIRE(str.GetLength() == stlStr.length());
			REQUIRE(std::strcmp(str.GetStringData(), stlStr.c_str()) == 0);
		}

		WHEN("Not empty stl-string")
		{
			std::string stlStr = "Hello, World!";

			CMyString str(stlStr);

			REQUIRE(str.GetLength() == stlStr.length());
			REQUIRE(std::strcmp(str.GetStringData(), stlStr.c_str()) == 0);
		}
	}

	GIVEN("Copying")
	{
		WHEN("Copy string")
		{
			auto initStr = "Hello, World!";

			CMyString str(initStr);
			CMyString str1(str);

			REQUIRE(std::strcmp(str.GetStringData(), str1.GetStringData()) == 0);
			REQUIRE(str.GetLength() == str1.GetLength());
		}

		WHEN("Copy with after changing")
		{
			auto initStr = "Hello, World!";

			CMyString str(initStr);
			CMyString str1(str);

			REQUIRE(std::strcmp(str.GetStringData(), str1.GetStringData()) == 0);
			REQUIRE(str.GetLength() == str1.GetLength());

			char* ptr = const_cast<char*>(str1.GetStringData());
			*ptr = 'h';
			REQUIRE(std::strcmp(str1.GetStringData(), initStr) == 1);
		}

		WHEN("Copying with symbols of end string")
		{
			auto initStr = "Hello\0,\0World!";

			CMyString str(initStr);

			REQUIRE(std::strcmp(str.GetStringData(), initStr) == 0);
			REQUIRE(str.GetLength() == std::strlen(initStr));
		}
	}
}

TEST_CASE("Getting substring")
{
	WHEN("Start position is 0")
	{
		CMyString str("Hello, World!");
		
		CMyString str1(str.SubString(0, 5));

		REQUIRE(std::strcmp(str1.GetStringData(), "Hello") == 0);
	}

	WHEN("Start position is > 0")
	{
		CMyString str("Hello, World!");

		CMyString str1(str.SubString(7, 5));

		REQUIRE(std::strcmp(str1.GetStringData(), "World") == 0);
	}

	WHEN("Start position is > length")
	{
		CMyString str("Hello, World!");

		THEN("Exception")
		{
			REQUIRE_THROWS(CMyString(str.SubString(str.GetLength() + 2, 5)));
		}
	}

	WHEN("Length is 0")
	{
		CMyString str("Hello, World!");

		CMyString str1(str.SubString(0, 0));

		REQUIRE(std::strcmp(str1.GetStringData(), "") == 0);
	}

	WHEN("\0 inside string")
	{
		CMyString str("Hello, \0World!", 14);

		CMyString str1 = str.SubString(8, 6);
		REQUIRE(std::strcmp(str1.GetStringData(), "World!") == 0);
	}
}

TEST_CASE("Getting capacity")
{
	WHEN("Capacity = default capacity value")
	{
		CMyString str("World!");

		REQUIRE(str.GetCapacity() == CMyString::s_defaultCapacity);
	}

	WHEN("String is cleared")
	{
		CMyString str("World!");
		size_t capacity = str.GetCapacity();
		str.Clear();

		REQUIRE(str.GetCapacity() == CMyString::s_defaultCapacity);
	}

	WHEN("Adding 1 symbol to string which length = default capacity value")
	{
		CMyString str("123456789012345");

		str += "1";

		REQUIRE(str.GetCapacity() == 2 * CMyString::s_defaultCapacity);
	}	
}

TEST_CASE("Getting length")
{
	WHEN("Empty string")
	{
		CMyString str;

		REQUIRE(str.GetLength() == 0);

	}

	WHEN("Not empty string")
	{
		CMyString str("Hello");

		REQUIRE(str.GetLength() == 5);

	}
}

TEST_CASE("Clearing string")
{
	WHEN("String is empty")
	{
		CMyString str;
		size_t capacity = str.GetCapacity();
		str.Clear();

		REQUIRE(str.GetLength() == 0);
		REQUIRE(str.GetCapacity() == capacity);
		REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
	}

	WHEN("String is not empty")
	{
		CMyString str("Hello, World!");
		size_t capacity = str.GetCapacity();
		str.Clear();

		REQUIRE(str.GetLength() == 0);
		REQUIRE(str.GetCapacity() == capacity);
		REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
	}
}

TEST_CASE("Overload operators")
{
	GIVEN("Operator+")
	{
		WHEN("CMyString + CMyString")
		{
			CMyString str("Hello, ");
			CMyString str1("World!");

			REQUIRE(str.GetLength() == 7);
			REQUIRE(str1.GetLength() == 6);

			CMyString str2 = str + str1;

			REQUIRE(std::strcmp(str2.GetStringData(), "Hello, World!") == 0);
		}

		WHEN("CMyString + STL-string")
		{
			CMyString str("Hello, ");
			std::string str1 = "World!";

			CMyString str2 = str + str1;

			REQUIRE(std::strcmp(str2.GetStringData(), "Hello, World!") == 0);
		}

		WHEN("STL-string + CMyString")
		{
			CMyString str("Hello, ");
			std::string str1 = "World!";

			CMyString str2 = str1 + str;

			REQUIRE(std::strcmp(str2.GetStringData(), "World!Hello, ") == 0);
		}

		WHEN("CMyString + const char*")
		{
			CMyString str("Hello, ");
			const char* str1 = "World!";

			CMyString str2 = str + str1;

			REQUIRE(std::strcmp(str2.GetStringData(), "Hello, World!") == 0);
		}

		WHEN("const char* + CMyString")
		{
			CMyString str("Hello, ");
			const char* str1 = "World!";

			CMyString str2 = str1 + str;

			REQUIRE(std::strcmp(str2.GetStringData(), "World!Hello, ") == 0);
		}
	}

	GIVEN("Operator+=")
	{
		CMyString str("Hello");
		CMyString str1(", World!");
		size_t capacity = str.GetCapacity();
		str += str1;

		REQUIRE(std::strcmp(str.GetStringData(), "Hello, World!") == 0);
		REQUIRE(str.GetCapacity() == CMyString::s_defaultCapacity);
	}

	GIVEN("Operator==")
	{
		WHEN("Strings are equals")
		{
			CMyString str("World!");
			CMyString str1(str);

			THEN("True")
			{
				REQUIRE(str == str1);
			}
		}

		WHEN("Strings are not equals")
		{
			CMyString str("World!");
			CMyString str1("World");

			THEN("False")
			{
				REQUIRE(!(str == str1));
			}
		}
	}

	GIVEN("Opeator!=")
	{
		WHEN("Strings are not equals")
		{
			CMyString str("World!");
			CMyString str1("World.");

			THEN("True")
			{
				REQUIRE(str != str1);
			}
		}

		WHEN("String are equals")
		{
			CMyString str("World!");
			CMyString str1("World!");

			THEN("False")
			{
				REQUIRE(!(str != str1));
			}
		}
	}

	GIVEN("Operator<")
	{
		WHEN("str1 < str2")
		{
			CMyString str1("abcc");
			CMyString str2("abcd");

			REQUIRE(str1 < str2);
		}

		WHEN("str1 > str2")
		{
			CMyString str1("abcc");
			CMyString str2("Abcc");

			REQUIRE(!(str1 < str2));
		}

		WHEN("Strings are equals")
		{
			CMyString str1("abcd");
			CMyString str2("abcd");

			REQUIRE(!(str1 < str2));
		}

		WHEN("str1 length < str2 length")
		{
			CMyString str1("abc");
			CMyString str2("abcd");

			REQUIRE(str1 < str2);
		}

		WHEN("str1 length > str2 length")
		{
			CMyString str1("aaaa");
			CMyString str2("aa");

			REQUIRE(!(str1 < str2));
		}
	}

	GIVEN("Operator>")
	{
		WHEN("str1 > str2")
		{
			CMyString str1("w");
			CMyString str2("A");

			REQUIRE(str1 > str2);
		}

		WHEN("str1 < str2")
		{
			CMyString str1("A");
			CMyString str2("a");

			REQUIRE(!(str1 > str2));
		}

		WHEN("Strings are equals")
		{
			CMyString str1("a");
			CMyString str2("a");

			REQUIRE(!(str1 > str2));
		}

		WHEN("str1 length < str2 length")
		{
			CMyString str1("a");
			CMyString str2("aa");

			REQUIRE(!(str1 > str2));
		}

		WHEN("str1 length > str2 length")
		{
			CMyString str1("aaa");
			CMyString str2("aa");

			REQUIRE(str1 > str2);
		}
	}

	GIVEN("Operator<=")
	{
		WHEN("str1 < str2")
		{
			CMyString str1("abcc");
			CMyString str2("abcd");

			REQUIRE(str1 <= str2);
		}

		WHEN("str1 > str2")
		{
			CMyString str1("abcc");
			CMyString str2("Abcc");

			REQUIRE(!(str1 <= str2));
		}

		WHEN("Strings are equals")
		{
			CMyString str1("abcd");
			CMyString str2("abcd");

			REQUIRE(str1 <= str2);
		}

		WHEN("str1 length < str2 length")
		{
			CMyString str1("abc");
			CMyString str2("abcd");

			REQUIRE(str1 <= str2);
		}

		WHEN("str1 length > str2 length")
		{
			CMyString str1("aaaa");
			CMyString str2("aa");

			REQUIRE(!(str1 <= str2));
		}
	}

	GIVEN("Operator>=")
	{
		WHEN("str1 > str2")
		{
			CMyString str1("w");
			CMyString str2("A");

			REQUIRE(str1 >= str2);
		}

		WHEN("str1 < str2")
		{
			CMyString str1("A");
			CMyString str2("a");

			REQUIRE(!(str1 >= str2));
		}

		WHEN("Strings are equals")
		{
			CMyString str1("a");
			CMyString str2("a");

			REQUIRE(str1 >= str2);
		}

		WHEN("str1 length < str2 length")
		{
			CMyString str1("a");
			CMyString str2("aa");

			REQUIRE(!(str1 >= str2));
		}

		WHEN("str1 length > str2 length")
		{
			CMyString str1("aaa");
			CMyString str2("aa");

			REQUIRE(str1 >= str2);
		}
	}

	GIVEN("Operator[] for writing")
	{
		WHEN("Correct transformation")
		{
			CMyString str("Hello, World!");

			str[0] = 'h';

			REQUIRE(std::strcmp(str.GetStringData(), "hello, World!") == 0);
		}

		WHEN("Index out of range")
		{
			CMyString str("Hello, World!");

			REQUIRE_THROWS_AS(str[20] = ' ', std::out_of_range);
		}
	}

	GIVEN("Operator[] for reading")
	{
		WHEN("Correct index")
		{
			CMyString str("Hello, World!");

			char c = str[0];

			REQUIRE(c == 'H');
		}

		WHEN("Index out of range")
		{
			CMyString str("Hello, World!");

			char c;

			REQUIRE_THROWS_AS(c = str[-1], std::out_of_range);
		}
	}

	GIVEN("Operator>>")
	{
		std::istringstream input("Hello, World!");

		CMyString str;

		input >> str;

		REQUIRE(std::strcmp(str.GetStringData(), "Hello,") == 0);
	}

	GIVEN("Opeator= &&")
	{
		CMyString str1 = "Hello, World!\nHello, World!";
		CMyString str2 = std::move(str1);

		REQUIRE(str1.GetCapacity() == CMyString::s_defaultCapacity);
		REQUIRE(str1.GetLength() == 0);
		REQUIRE(std::strcmp(str1.GetStringData(), "") == 0);
	}
}

