#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../Date/stdafx.h"
#include "../Date/CDate.h"
#include <sstream>
const unsigned MAX_DAYS_COUNT = 2932896;

TEST_CASE("Test date constructor")
{
	GIVEN("Test date constructor from day, month and year")
	{
		WHEN("Year < acceptable year(1970)")
		{
			unsigned day = 1, year = 1969;
			Month month = Month::JANUARY;
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("Year > acceptable year(9999)")
		{
			unsigned day = 1, year = 10000;
			Month month = Month::JANUARY;
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("Not existing month = 0")
		{
			unsigned day = 1, year = 10000;
			Month month = static_cast<Month>(0);
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("Not existing month = 13")
		{
			unsigned day = 1, year = 10000;
			Month month = static_cast<Month>(13);
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("Day = 0")
		{
			unsigned day = 0, year = 1970;
			Month month = Month::JANUARY;
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("Day = 32")
		{
			unsigned day = 32, year = 1970;
			Month month = Month::JANUARY;
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("29 of february in not leap year")
		{
			unsigned day = 29, year = 1970;
			Month month = Month::FEBRUARY;
			THEN("Return except")
			{
				REQUIRE_THROWS_AS(CDate(day, month, year), std::out_of_range);
			}
		}

		WHEN("29 february in leap year")
		{
			unsigned day = 29, year = 1972;
			Month month = Month::FEBRUARY;
			THEN("No except")
			{
				REQUIRE_NOTHROW(CDate(day, month, year));
			}
		}

		WHEN("Min acceptable year")
		{
			unsigned day = 1, year = 1970;
			Month month = Month::JANUARY;
			THEN("No except")
			{
				REQUIRE_NOTHROW(CDate(day, month, year));
			}
		}

		WHEN("Max acceptable year")
		{
			unsigned day = 1, year = 9999;
			Month month = Month::JANUARY;
			THEN("No except")
			{
				REQUIRE_NOTHROW(CDate(day, month, year));
			}
		}
	}
	//TODO: проверить дни по двум границам
	GIVEN("Test date constructor from timestamp")
	{
		WHEN("Days number is incorrect")
		{
			REQUIRE_THROWS_AS(CDate(-1), std::out_of_range);
		}

		WHEN("Days number is correct")
		{
			REQUIRE_NOTHROW(CDate(0));
		}

		WHEN("Days number is correct")
		{
			REQUIRE_NOTHROW(CDate(9000));
		}

		WHEN("Days in max (correct)")
		{
			REQUIRE_NOTHROW(CDate(MAX_DAYS_COUNT));
		}

		WHEN("Days in max (incorrect)")
		{
			REQUIRE_THROWS_AS(CDate(MAX_DAYS_COUNT + 1), std::out_of_range);
		}
	}

	GIVEN("Test date default constructor")
	{
		WHEN("Check for excepts")
		{
			REQUIRE_NOTHROW(CDate());
		}
	}
}

TEST_CASE("Counting days check")
{
	WHEN("Date is min")
	{
		unsigned day = 1;
		unsigned year = 1970;
		Month month = Month::JANUARY;
		CDate date(day, month, year);
		REQUIRE(date.GetYear() == year);
		REQUIRE(date.GetMonth() == month);
		REQUIRE(date.GetDay() == day);
	}

	WHEN("Date is max")
	{
		unsigned day = 31;
		unsigned year = 9999;
		Month month = Month::DECEMBER;
		CDate date(day, month, year);
		REQUIRE(date.GetYear() == year);
		REQUIRE(date.GetMonth() == month);
		REQUIRE(date.GetDay() == day);
	}
}

TEST_CASE("Check method of getting year")
{
	GIVEN("Given a timestamp")
	{
		WHEN("Date is 01.01.1970")
		{
			CDate date(0);
			REQUIRE(date.GetYear() == 1970);
		}

		WHEN("Date is 01.01.1971")
		{
			CDate date(365);
			REQUIRE(date.GetYear() == 1971);
		}

		WHEN("Date is 31.12.1976")
		{
			CDate date(2556);
			REQUIRE(date.GetYear() == 1976);
		}

		WHEN("Date is 01.01.1977")
		{
			CDate date(2557);
			REQUIRE(date.GetYear() == 1977);
		}

		WHEN("Date is 01.01.1973 (after leap year)")
		{
			CDate date(1096);
			REQUIRE(date.GetYear() == 1973);
		}

		WHEN("Date is 31.12.1972 (end of leap year)")
		{
			CDate date(1095);
			REQUIRE(date.GetYear() == 1972);
		}

		WHEN("Date is max")
		{
			CDate date(MAX_DAYS_COUNT);
			REQUIRE(date.GetDay() == 31);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetYear() == 9999);
		}
		//TODO: проверка максимальной даты
	}

	GIVEN("Given a date")
	{
		WHEN("Date is 01.01.1970")
		{
			CDate date(1, static_cast<Month>(1), 1970);
			REQUIRE(date.GetYear() == 1970);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetDay() == 1);
		}

		WHEN("Date is 31.12.1972 (in leap year)")
		{
			CDate date(31, static_cast<Month>(12), 1972);
			REQUIRE(date.GetYear() == 1972);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetDay() == 31);
		}

		WHEN("Date is 01.01.1973 (after leap year)")
		{
			CDate date(1, static_cast<Month>(1), 1973);
			REQUIRE(date.GetYear() == 1973);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetDay() == 1);
		}

		WHEN("Date is 31.12.1976 (in leap year)")
		{
			CDate date(31, static_cast<Month>(12), 1976);
			REQUIRE(date.GetDaysNum() == 2556);
			REQUIRE(date.GetYear() == 1976);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetDay() == 31);
		}

		WHEN("Date is 01.01.1977 (after leap year)")
		{
			CDate date(1, static_cast<Month>(1), 1977);
			REQUIRE(date.GetYear() == 1977);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetDay() == 1);
		}

		WHEN("Date is 01.01.9999")
		{
			CDate date(1, static_cast<Month>(1), 9999);
			REQUIRE(date.GetYear() == 9999);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetDay() == 1);
		}
	}
}

TEST_CASE("Check method of getting month")
{
	GIVEN("Month is JAN")
	{
		Month month = static_cast<Month>(1);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetDaysNum() == 9496);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetDaysNum() == 9526);
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is FEB")
	{
		Month month = static_cast<Month>(2);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetDaysNum() == 9527);
			REQUIRE(date.GetMonth() == month);

			date = { 29, month, 1996 };
			REQUIRE(date.GetDaysNum() == 9555);
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 28, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is MAR")
	{
		Month month = static_cast<Month>(3);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is APR")
	{
		Month month = static_cast<Month>(4);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is MAY")
	{
		Month month = static_cast<Month>(5);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is JUN")
	{
		Month month = static_cast<Month>(6);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is JUL")
	{
		Month month = static_cast<Month>(7);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is AUG")
	{
		Month month = static_cast<Month>(8);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is SEP")
	{
		Month month = static_cast<Month>(9);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is OCT")
	{
		Month month = static_cast<Month>(10);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is NOV")
	{
		Month month = static_cast<Month>(11);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}

	GIVEN("Month is DEC")
	{
		Month month = static_cast<Month>(12);
		WHEN("Leap year")
		{
			CDate date(1, month, 1996);
			REQUIRE(date.GetMonth() == month);

			date = { 30, month, 1996 };
			REQUIRE(date.GetMonth() == month);
		}

		WHEN("Not leap year")
		{
			CDate date(1, month, 9999);
			REQUIRE(date.GetMonth() == month);

			date = { 31, month, 9999 };
			REQUIRE(date.GetMonth() == month);
		}
	}
}

TEST_CASE("Check method of getting day")
{
	GIVEN("When year is leap")
	{
		unsigned day = 1;
		unsigned year = 1976;
		WHEN("Month is JAN")
		{
			Month month = Month::JANUARY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);
			
			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is FEB")
		{
			Month month = Month::FEBRUARY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 29;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is MAR")
		{
			Month month = Month::MARCH;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is APR")
		{
			Month month = Month::APRIL;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is MAY")
		{
			Month month = Month::MAY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is JUN")
		{
			Month month = Month::JUNE;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is JUL")
		{
			Month month = Month::JULY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is AUG")
		{
			Month month = Month::AUGUST;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is SEP")
		{
			Month month = Month::SEPTEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is OCT")
		{
			Month month = Month::OCTOBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is NOV")
		{
			Month month = Month::NOVEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is DEC")
		{
			Month month = Month::DECEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}
	}

	GIVEN("When year is not leap")
	{
		unsigned day = 1;
		unsigned year = 1977;
		WHEN("Month is JAN")
		{
			Month month = Month::JANUARY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is FEB")
		{
			Month month = Month::FEBRUARY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 28;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is MAR")
		{
			Month month = Month::MARCH;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is APR")
		{
			Month month = Month::APRIL;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is MAY")
		{
			Month month = Month::MAY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is JUN")
		{
			Month month = Month::JUNE;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is JUL")
		{
			Month month = Month::JULY;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is AUG")
		{
			Month month = Month::AUGUST;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is SEP")
		{
			Month month = Month::SEPTEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is OCT")
		{
			Month month = Month::OCTOBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is NOV")
		{
			Month month = Month::NOVEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 30;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}

		WHEN("Month is DEC")
		{
			Month month = Month::DECEMBER;
			CDate date(day, month, year);
			REQUIRE(date.GetDay() == day);

			day = 31;
			date = { day, month, year };
			REQUIRE(date.GetDay() == day);
		}
	}

}

TEST_CASE("Check method of getting week day")
{
	WHEN("Week day is sunday")
	{
		CDate date(5, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);
	}

	WHEN("Week day is monday")
	{
		CDate date(6, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);
	}

	WHEN("Week day is tuesday")
	{
		CDate date(7, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::TUESDAY);
	}

	WHEN("Week day is wednesday")
	{
		CDate date(8, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
	}

	WHEN("Week day is thursday")
	{
		CDate date(9, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
	}

	WHEN("Week day is friday")
	{
		CDate date(10, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
	}

	WHEN("Week day is saturday")
	{
		CDate date(11, static_cast<Month>(5), 2024);
		REQUIRE(date.GetWeekDay() == WeekDay::SATURDAY);
	}
}

TEST_CASE("Test date modifying operators")
{
	GIVEN("Test operator++")
	{
		unsigned year = 1976,
			day = 1;
		Month month = Month::JANUARY;
		WHEN("Date is not max")
		{
			CDate date(day, month, year);
			date++;
			REQUIRE(date.GetDay() == 2);
		}

		WHEN("Date is max")
		{
			CDate date(31, static_cast<Month>(12), 9999);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(date++, std::out_of_range);
			}
		}
	}

	GIVEN("Test ++operator")
	{
		unsigned year = 1976,
			day = 1;
		Month month = Month::JANUARY;
		WHEN("Date is not max")
		{
			CDate date(day, month, year);
			++date;
			REQUIRE(date.GetDay() == 2);
		}

		WHEN("Date is max")
		{
			CDate date(31, static_cast<Month>(12), 9999);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(++date, std::out_of_range);
			}
		}
	}

	GIVEN("Test operator--")
	{
		unsigned year = 1976,
			day = 31;
		Month month = Month::JANUARY;
		WHEN("Date is not min")
		{
			CDate date(day, month, year);
			date--;
			REQUIRE(date.GetDay() == 30);
		}

		WHEN("Date is min")
		{
			CDate date(1, static_cast<Month>(1), 1970);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(date--, std::out_of_range);
			}
		}
	}

	GIVEN("Test --operator")
	{
		unsigned year = 1976,
			day = 31;
		Month month = Month::JANUARY;
		WHEN("Date is not min")
		{
			CDate date(day, month, year);
			--date;
			REQUIRE(date.GetDay() == 30);
		}

		WHEN("Date is min")
		{
			CDate date(1, static_cast<Month>(1), 1970);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(--date, std::out_of_range);
			}
		}
	}

	GIVEN("Test operator+")
	{
		unsigned year = 1976,
			day = 31;
		Month month = Month::DECEMBER;
		WHEN("Date is not max")
		{
			CDate date(day, month, year);
			CDate date2 = date + 3;
			REQUIRE(date2.GetDay() == 3);
			REQUIRE(date2.GetMonth() == Month::JANUARY);
			REQUIRE(date2.GetYear() == year + 1);

			date2 = 3 + date;
			REQUIRE(date2.GetDay() == 3);
			REQUIRE(date2.GetMonth() == Month::JANUARY);
			REQUIRE(date2.GetYear() == year + 1);
		}

		year = 9999;
		month = Month::DECEMBER;
		WHEN("Date is max")
		{
			CDate date(day, month, year);
			REQUIRE_THROWS_AS(date + 3, std::out_of_range);
			REQUIRE_THROWS_AS(3 + date, std::out_of_range);
		}
	}

	GIVEN("Test operator-")
	{
		unsigned year = 1976,
			day = 31;
		Month month = Month::DECEMBER;
		WHEN("Date is not min (date - num)")
		{
			CDate date(day, month, year);
			CDate date2 = date - 30;
			REQUIRE(date2.GetDay() == 1);
			REQUIRE(date2.GetMonth() == month);
			REQUIRE(date2.GetYear() == year);
		}

		WHEN("Date is min (date - num)")
		{
			CDate date(1, static_cast<Month>(1), 1970);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(date - 5, std::out_of_range);
			}
		}

		WHEN("Date - num (negative)")
		{
			int num = -5;
			unsigned day = 1,
				year = 1970;
			Month month = static_cast<Month>(1);
			CDate date(day, month, year);
			THEN("Success")
			{
				CDate date2 = date - num;
				REQUIRE(date2.GetDay() == day + 5);
				REQUIRE(date2.GetMonth() == month);
				REQUIRE(date2.GetYear() == year);
			}
		}

		WHEN("Date - date")
		{
			CDate date(31, month, year);
			CDate date2(1, month, year);
			unsigned days = date - date2;
			REQUIRE(days == 30);
		}
	}

	GIVEN("Test operator+=")
	{
		WHEN("Date is not max")
		{
			unsigned day = 1,
				year = 1970;
			Month month = static_cast<Month>(1);
			CDate date(day, month, year);
			date += 3;
			REQUIRE(date.GetDay() == day + 3);
			REQUIRE(date.GetMonth() == month);
			REQUIRE(date.GetYear() == year);
		}

		WHEN("Date is max")
		{
			unsigned day = 31,
				year = 9999;
			Month month = static_cast<Month>(12);
			CDate date(day, month, year);
			REQUIRE_THROWS_AS(date += 3, std::out_of_range);
		}
	}

	GIVEN("Test operator-=")
	{
		WHEN("Date is not min")
		{
			unsigned day = 31,
				year = 1970;
			Month month = static_cast<Month>(1);
			CDate date(day, month, year);
			date -= 3;
			REQUIRE(date.GetDay() == day - 3);
			REQUIRE(date.GetMonth() == month);
			REQUIRE(date.GetYear() == year);
		}

		WHEN("Date is min")
		{
			unsigned day = 1,
				year = 1970;
			Month month = static_cast<Month>(1);
			CDate date(day, month, year);
			REQUIRE_THROWS_AS(date -= 3, std::out_of_range);
		}
	}

	GIVEN("Test out date")
	{
		unsigned day = 1,
			year = 1970;
		Month month = static_cast<Month>(1);
		CDate date(day, month, year);
		std::ostringstream output;
		output << date;
		REQUIRE(output.str() == "01.01.1970");
	}

	GIVEN("Test reading date from stream")
	{
		WHEN("Date is correct")
		{
			std::istringstream input("01.01.1970");
			CDate date(365);
			input >> date;
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == static_cast<Month>(1));
			REQUIRE(date.GetYear() == 1970);
		}

		WHEN("Date is correct (without zeros)")
		{
			std::istringstream input("1.1.1970");
			CDate date(365);
			input >> date;
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == static_cast<Month>(1));
			REQUIRE(date.GetYear() == 1970);
		}

		WHEN("Date is incorrect")
		{
			std::istringstream input("lol");
			CDate date(365);
			THEN("Except")
			{
				REQUIRE_THROWS_AS(input >> date, std::logic_error);
			}
		}
	}

	GIVEN("Test comparison operators")
	{
		WHEN("Operator == (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(date1 == date2);
		}

		WHEN("Operator == (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(!(date1 == date2));
		}

		WHEN("Operator != (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(!(date1 != date2));
		}

		WHEN("Operator != (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(date1 != date2);
		}

		WHEN("Operator < (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(!(date1 < date2));
		}

		WHEN("Operator < (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(date1 < date2);
		}

		WHEN("Operator > (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(!(date1 > date2));
		}

		WHEN("Operator > (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(date2 > date1);
		}

		WHEN("Operator <= (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(date1 <= date2);
		}

		WHEN("Operator <= (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(date1 <= date2);
		}

		WHEN("Operator >= (dates equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(1, static_cast<Month>(1), 1970);
			REQUIRE(date1 >= date2);
		}

		WHEN("Operator <= (dates not equals)")
		{
			CDate date1(1, static_cast<Month>(1), 1970);
			CDate date2(2, static_cast<Month>(1), 1970);
			REQUIRE(date2 >= date1);
		}
	}
}