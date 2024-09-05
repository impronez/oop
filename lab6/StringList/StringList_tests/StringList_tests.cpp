#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../StringList/CStringList.h"
#include <iterator>

TEST_CASE("Creating constructor")
{
	CStringList list;

	REQUIRE(list.GetSize() == 0);
	REQUIRE(list.IsEmpty());
}

TEST_CASE("List copying")
{
	CStringList list;
	list.PushBack("test1");
	list.PushBack("test2");

	WHEN("With copying constructor")
	{
		CStringList listCopy{ list };
		REQUIRE(list.GetSize() == listCopy.GetSize());
		REQUIRE(*list.begin() == *listCopy.begin());
	}

	WHEN("With copying operator")
	{
		CStringList listCopy = list;
		REQUIRE(list.GetSize() == listCopy.GetSize());
		REQUIRE(*list.begin() == *listCopy.begin());
	}
}

TEST_CASE("List moving")
{
	CStringList list;
	list.PushBack("test1");
	list.PushBack("test2");
	size_t size = list.GetSize();

	WHEN("With moving constructor")
	{
		CStringList listMove{ std::move(list) };

		REQUIRE(listMove.GetSize() == size);
		REQUIRE(*listMove.begin() == "test1");

		REQUIRE(list.IsEmpty());
	}

	WHEN("With moving operator")
	{
		CStringList listMove = std::move(list);

		REQUIRE(listMove.GetSize() == size);
		REQUIRE(*listMove.begin() == "test1");

		REQUIRE(list.IsEmpty());
	}
}

TEST_CASE("Elements adding")
{
	CStringList list;

	GIVEN("Push front")
	{
		WHEN("Push front 1 elem")
		{
			std::string str = "test";
			list.PushFront(str);

			REQUIRE(list.GetSize() == 1);
			REQUIRE(*list.begin() == str);
		}

		WHEN("Push front 3 elem")
		{
			list.PushFront("test1");
			list.PushFront("test2");
			list.PushFront("test3");

			REQUIRE(list.GetSize() == 3);
			REQUIRE(*list.begin() == "test3");
		}
	}

	GIVEN("Push back")
	{
		WHEN("Push back 1 elem")
		{
			std::string str = "test";
			list.PushBack(str);

			REQUIRE(list.GetSize() == 1);
			REQUIRE(*list.begin() == str);
		}

		WHEN("Push back 3 elem")
		{
			list.PushBack("test1");
			list.PushBack("test2");
			list.PushBack("test3");

			REQUIRE(list.GetSize() == 3);
			REQUIRE(*list.begin() == "test1");
		}
	}

	GIVEN("Insert")
	{
		WHEN("Insert in beginning")
		{
			auto it = list.begin();
			list.Insert(it, "testing");

			REQUIRE(list.GetSize() == 1);
			REQUIRE(*list.begin() == "testing");
		}

		WHEN("Insert in end")
		{
			auto it = list.end();
			list.Insert(it, "testing");

			REQUIRE(list.GetSize() == 1);
			REQUIRE(*list.begin() == "testing");
		}

		WHEN("Insert in list middle")
		{
			list.PushBack("test1");
			list.PushBack("test2");
			list.PushBack("test4");

			auto it = ++(++(list.begin()));
			list.Insert(it, "test3");
			
			REQUIRE(list.GetSize() == 4);
			REQUIRE(*(++(++(list.begin()))) == "test3");
		}
	}
}

TEST_CASE("Elements deleting")
{
	CStringList list;
	list.PushBack("test1");
	list.PushBack("test2");

	WHEN("Delete 1 elem")
	{
		auto it = list.begin();
		list.Delete(it);

		REQUIRE(list.GetSize() == 1);
		REQUIRE(*list.begin() == "test2");
	}

	WHEN("List clearing")
	{
		list.Clear();

		REQUIRE(list.IsEmpty());
	}
}

TEST_CASE("Size getting")
{
	CStringList list;
	for (int i = 0; i < 5; i++)
	{
		list.PushBack("test");
	}
	
	WHEN("After elements adding")
	{
		REQUIRE(list.GetSize() == 5);
	}

	WHEN("After deleting 1 elem")
	{
		list.Delete(list.begin());

		REQUIRE(list.GetSize() == 4);
	}

	WHEN("After element inserting")
	{
		list.Insert(list.begin(), "test");

		REQUIRE(list.GetSize() == 6);
	}

	WHEN("After list clearing")
	{
		list.Clear();

		REQUIRE(list.GetSize() == 0);
	}
}

TEST_CASE("Checking for emptiness")
{
	CStringList list;

	WHEN("List is empty")
	{
		REQUIRE(list.IsEmpty());
	}

	WHEN("There are elements")
	{
		list.PushBack("test");
		list.PushBack("test");
		list.PushBack("test");
	
		REQUIRE(!list.IsEmpty());
	}
}

TEST_CASE("Iterator")
{
	CStringList list;
	list.PushBack("test");
	list.PushBack("data");

	WHEN("Test operator==")
	{
		auto first = list.begin(),
			second = list.end();
		REQUIRE(!(second == first));

		second = list.begin();
		REQUIRE(first == second);
	}

	WHEN("Test operator!=")
	{
		auto first = list.begin(),
			second = list.end();
		REQUIRE(second != first);

		second = list.begin();
		REQUIRE(!(first != second));
	}

	WHEN("Test operator++ (prefix)")
	{
		auto it = list.begin();
		std::string str = *(++(it));

		REQUIRE(str == "data");
	}

	WHEN("Test operator++ (postfix)")
	{
		auto it = list.begin();
		std::string str = *((it)++);

		REQUIRE(str == "test");
	}

	WHEN("Test operator-- (prefix)")
	{
		auto it = list.end();
		std::string str = *(--(it));

		REQUIRE(str == "data");
	}

	WHEN("Test operator++ (postfix)")
	{
		auto it = list.end();
		std::string str = *((--it)--);

		REQUIRE(str == "data");
	}

	WHEN("Data getting")
	{
		auto it = list.begin();

		REQUIRE(*it == "test");
	}
}

TEST_CASE("Const iterator")
{
	CStringList tmp;
	tmp.PushBack("test1");
	tmp.PushBack("test2");

	const CStringList list = tmp;

	WHEN("Test operator==")
	{
		auto first = list.begin(),
			second = list.end();
		REQUIRE(!(second == first));

		second = list.begin();
		REQUIRE(first == second);
	}

	WHEN("Test operator!=")
	{
		auto first = list.begin(),
			second = list.end();
		REQUIRE(second != first);

		second = list.begin();
		REQUIRE(!(first != second));
	}

	WHEN("Test operator++ (prefix)")
	{
		auto it = list.begin();
		std::string str = *(++(it));

		REQUIRE(str == "test2");
	}

	WHEN("Test operator++ (postfix)")
	{
		auto it = list.begin();
		std::string str = *((it)++);

		REQUIRE(str == "test1");
	}

	WHEN("Test operator-- (prefix)")
	{
		auto it = list.end();
		std::string str = *(--(it));

		REQUIRE(str == "test2");
	}

	WHEN("Test operator++ (postfix)")
	{
		auto it = list.end();
		std::string str = *((--it)--);

		REQUIRE(str == "test2");
	}

	WHEN("Test operator*")
	{
		auto it = list.begin();

		REQUIRE(*it == "test1");
	}
}