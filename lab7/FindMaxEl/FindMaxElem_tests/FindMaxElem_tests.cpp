#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../FindMaxEl/FindMax.hpp"

struct SportsmanInfo
{
	std::string firstName;
	std::string lastName;
	std::string middleName;
	double height;
	double weight;
};

bool CompareByWeight(const SportsmanInfo& first, const SportsmanInfo& second)
{
	return first.weight < second.weight;
}

bool CompareByHeight(const SportsmanInfo& first, const SportsmanInfo& second)
{
	return first.height < second.height;
}	

const std::vector<SportsmanInfo> records =
{
	{ "Иванов", "Иван", "Иванович", 185.2, 93 },
	{ "Петров", "Петр", "Петрович", 185, 90 },
	{ "Пупкин", "Василий", "Васильевич", 175.5, 100 }
};

TEST_CASE("Empty array")
{
	std::vector<SportsmanInfo> emptyRecords{};
	SportsmanInfo record;
	
	REQUIRE(!FindMax(emptyRecords, record, CompareByHeight));
}

TEST_CASE("Array witn 1 elem")
{
	std::vector<SportsmanInfo> arr(1, { "Иванов", "Иван", "Иванович", 175, 80 });
	SportsmanInfo record{};

	bool isSuccess = FindMax(arr, record, CompareByHeight);
	REQUIRE(isSuccess);
	
	REQUIRE(arr.front().firstName == record.firstName);
	REQUIRE(arr.front().lastName == record.lastName);
	REQUIRE(arr.front().middleName == record.middleName);
	REQUIRE(arr.front().height == record.height);
	REQUIRE(arr.front().weight == record.weight);
}

TEST_CASE("Compare by height")
{
	SportsmanInfo record{};

	bool isSuccess = FindMax(records, record, CompareByHeight);

	REQUIRE(record.firstName == "Иванов");
	REQUIRE(record.lastName == "Иван");
	REQUIRE(record.middleName == "Иванович");
	REQUIRE(record.height == 185.2);
	REQUIRE(record.weight == 93);
}

TEST_CASE("Compare by weight")
{
	SportsmanInfo record{};

	bool isSuccess = FindMax(records, record, CompareByWeight);

	REQUIRE(record.firstName == "Пупкин");
	REQUIRE(record.lastName == "Василий");
	REQUIRE(record.middleName == "Васильевич");
	REQUIRE(record.height == 175.5);
	REQUIRE(record.weight == 100);
}
