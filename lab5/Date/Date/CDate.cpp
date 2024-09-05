#include "CDate.h"
#include <map>

const std::map<Month, unsigned> CDate::DAYS_IN_MONTHS =
{
	{ Month::JANUARY, 31 },
	{ Month::FEBRUARY, 28 },
	{ Month::MARCH, 31 },
	{ Month::APRIL, 30 },
	{ Month::MAY, 31 },
	{ Month::JUNE, 30 },
	{ Month::JULY, 31 },
	{ Month::AUGUST, 31 },
	{ Month::SEPTEMBER, 30 },
	{ Month::OCTOBER, 31 },
	{ Month::NOVEMBER, 30 },
	{ Month::DECEMBER, 31 }
};

const std::map<unsigned, Month> CDate::DAYS_AFTER_EVERY_MONTH =
{
	{31, Month::JANUARY},
	{59, Month::FEBRUARY},
	{90, Month::MARCH},
	{120, Month::APRIL},
	{151, Month::MAY},
	{181, Month::JUNE},
	{212, Month::JULY},
	{243, Month::AUGUST},
	{273, Month::SEPTEMBER},
	{304, Month::OCTOBER},
	{334, Month::NOVEMBER},
	{365, Month::DECEMBER}
};

const std::map<unsigned, Month> CDate::DAYS_AFTER_EVERY_MONTH_IN_LEAP_YEAR =
{
	{31, Month::JANUARY},
	{60, Month::FEBRUARY},
	{91, Month::MARCH},
	{121, Month::APRIL},
	{152, Month::MAY},
	{182, Month::JUNE},
	{213, Month::JULY},
	{244, Month::AUGUST},
	{274, Month::SEPTEMBER},
	{305, Month::OCTOBER},
	{335, Month::NOVEMBER},
	{366, Month::DECEMBER}
};

const unsigned CDate::MAX_DAYS_COUNT = 2932896;

const char SEPARATOR = '.';
const unsigned DAYS_IN_WEEK = 7;
const unsigned MIN_YEAR = 1970;
const unsigned MAX_YEAR = 9999;
const unsigned FIRST_LEAP_YEAR = 1972;
const unsigned DAYS_IN_YEAR = 365;
const double EXACT_DAYS_IN_YEAR = 365.25;
const unsigned DAYS_IN_2_YEARS = 730;
const int DAYS_FROM_1970_TO_2000 = 10957;
const int DAYS_IN_100_YEARS = 36525;
const int DAYS_IN_400_YEARS = 146097;

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		throw std::out_of_range("Incorrect year!");
	}
	bool isLeapYear = IsLeapYear(year);

	if (month < Month::JANUARY || month > Month::DECEMBER)
	{
		throw std::out_of_range("Incorrect month!");
	}

	if (!IsCorrectDayForMonth(day, month, isLeapYear))
	{
		throw std::out_of_range("Incorrect num of day for this month!");
	}
	
	m_days = CountTimestamp(day, month, year);
}
//TODO: проверка на верхнюю границу +
CDate::CDate(unsigned timestamp)
{
	if (timestamp > MAX_DAYS_COUNT)
	{
		throw std::out_of_range("Incorrect value of days!");
	}

	m_days = timestamp;
}

unsigned CDate::GetDay() const
{
	unsigned year = CDate::GetYear();
	Month month = CDate::GetMonth();
	unsigned days = m_days;
	bool isLeapYear = IsLeapYear(year);
	
	DaysCounting(days, year);

	if (isLeapYear)
	{
		days++;
		return GetDayByCountOfDays(days, DAYS_AFTER_EVERY_MONTH_IN_LEAP_YEAR);
	}
	else
	{
		return GetDayByCountOfDays(days, DAYS_AFTER_EVERY_MONTH);
	}
}

Month CDate::GetMonth() const
{
	unsigned year = CDate::GetYear();
	unsigned days = m_days;
	bool isLeapYear = IsLeapYear(year);
	
	DaysCounting(days, year);

	if (!isLeapYear)
	{
		if (days != 0)
		{
			days--;
		}
		return GetMonthByDays(days, DAYS_AFTER_EVERY_MONTH);
	}
	else
	{
		return GetMonthByDays(days, DAYS_AFTER_EVERY_MONTH_IN_LEAP_YEAR);
	}
}

unsigned CDate::GetYear() const
{
	unsigned year = 0;
	int days = static_cast<int>(m_days);

	if (days > DAYS_IN_2_YEARS)
	{
		days -= DAYS_IN_2_YEARS;
	}
	else
	{
		return static_cast<unsigned>(MIN_YEAR + (days / DAYS_IN_YEAR));
	}

	if ((days - DAYS_FROM_1970_TO_2000) > DAYS_IN_100_YEARS) // in 100 years
	{
		days += ((days - DAYS_FROM_1970_TO_2000) / DAYS_IN_100_YEARS);
	}

	if ((days - DAYS_FROM_1970_TO_2000) > DAYS_IN_400_YEARS) // in 400 years
	{
		days -= ((days - DAYS_FROM_1970_TO_2000) / DAYS_IN_400_YEARS);
	}

	year = static_cast<unsigned>(FIRST_LEAP_YEAR + (days / EXACT_DAYS_IN_YEAR));

	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_days + 4) % DAYS_IN_WEEK);
}

CDate& CDate::operator++()
{
	if (m_days == MAX_DAYS_COUNT)
	{
		throw std::out_of_range("Date is max!");
	}
	m_days++;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate tmpCopy(*this);
	++(*this);
	return tmpCopy;
}

CDate& CDate::operator--()
{
	if (m_days == 0)
	{
		throw std::out_of_range("Date is min!");
	}
	m_days--;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate tmpCopy(*this);
	--(*this);
	return tmpCopy;
}

CDate CDate::operator+(int days) const
{
	if (m_days + days > MAX_DAYS_COUNT)
	{
		throw std::out_of_range("Out the max value range!");
	}
	return CDate(m_days + days);
}

CDate CDate::operator-(int days) const
{
	if (static_cast<int>(m_days) - days < 0)
	{
		throw std::out_of_range("Out the min value range!");
	}
	return CDate(m_days - days);
}

int CDate::operator-(const CDate& date) const
{
	return m_days - date.m_days;
}

CDate& CDate::operator+=(int days)
{
	if (m_days + days > MAX_DAYS_COUNT)
	{
		throw std::out_of_range("Out the max value range!");
	}
	m_days += days;
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (static_cast<int>(m_days) - days < 0)
	{
		throw std::out_of_range("Out the min value range!");
	}
	m_days -= days;
	return *this;
}

std::ostream& operator<<(std::ostream& ostream, const CDate& date)
{
	unsigned day = date.GetDay();
	unsigned month = static_cast<unsigned>(date.GetMonth());
	unsigned year = date.GetYear();
	ostream << std::setfill('0') << std::setw(2) << day << SEPARATOR
		<< std::setfill('0') << std::setw(2) << month << SEPARATOR
		<< year;

	return ostream;
}

std::istream& operator>>(std::istream& istream, CDate& date)
{
	unsigned day, month, year;
	char firstDote, secondDote;
	if (!(istream >> day >> firstDote >> month >> secondDote >> year))
	{
		throw std::logic_error("Incorrect date!");
	}
	if (firstDote != SEPARATOR || secondDote != SEPARATOR)
	{
		throw std::logic_error("Incorrect form date!");
	}

	date = CDate(day, static_cast<Month>(month), year);
	return istream;
}

bool CDate::operator==(const CDate& date) const
{
	return m_days == date.m_days;
}

bool CDate::operator!=(const CDate& date) const
{
	return m_days != date.m_days;
}

bool CDate::operator<(const CDate& date) const
{
	return m_days < date.m_days;
}

bool CDate::operator>(const CDate& date) const
{
	return m_days > date.m_days;
}

bool CDate::operator<=(const CDate& date) const
{
	return m_days <= date.m_days;
}

bool CDate::operator>=(const CDate& date) const
{
	return m_days >= date.m_days;
}

CDate operator+(int days, const CDate& date)
{
	return date + days;
}

bool CDate::IsLeapYear(unsigned year)
{
	if ((year % 100) == 0)
	{
		return (year % 400) == 0;
	}
	return (year % 4) == 0;
}

bool CDate::IsCorrectDayForMonth(unsigned day, Month month, bool isLeapYear)
{
	auto maxCountDaysInMonth = DAYS_IN_MONTHS.at(month);
	if (isLeapYear && month == Month::FEBRUARY)
	{
		maxCountDaysInMonth++;
	}

	return ((day >= 1) && (day <= maxCountDaysInMonth));
}

unsigned CDate::CountTimestamp(unsigned day, Month currentMonth, unsigned year)
{
	unsigned countOfDays = day - 1;

	for (int i = 1; i < static_cast<int>(currentMonth); i++)
	{
		Month month = static_cast<Month>(i);
		countOfDays += DAYS_IN_MONTHS.at(month);
	}

	int yearsNum = year - MIN_YEAR;
	bool isLeapYear = IsLeapYear(year);
	if (yearsNum > 0)
	{
		countOfDays += DAYS_IN_YEAR * yearsNum;

		if (!isLeapYear && (yearsNum + 2) / 4 > 0)
		{
			countOfDays += (yearsNum + 2) / 4;
		}
		else if (isLeapYear && (yearsNum / 4) > 0)
		{
			countOfDays += yearsNum / 4;
		}
	}
	if (currentMonth > Month::FEBRUARY && isLeapYear)
	{
		countOfDays++;
	}
	if (year >= 2100)
	{
		countOfDays -= (yearsNum - 30) / 100;
		countOfDays += (yearsNum - 30) / 400;
	}

	return countOfDays;
}

Month CDate::GetMonthByDays(const unsigned days, const std::map<unsigned, Month>& map)
{
	for (auto it = map.begin(); it != map.end(); it++)
	{
		if (days < it->first)
		{
			return it->second;
		}
	}
}

unsigned CDate::GetDayByCountOfDays(unsigned days, const std::map<unsigned, Month>& map)
{
	auto it = map.lower_bound(days);
	if (it == map.begin())
	{
		if (days == 0)
		{
			return 1;
		}
		return days;
	}
	it--;
	return (days - it->first);
}

void CDate::DaysCounting(unsigned& days, unsigned year)
{
	if (year >= FIRST_LEAP_YEAR)
	{
		days -= DAYS_IN_2_YEARS; 
		year -= FIRST_LEAP_YEAR; 
	}
	else
	{
		year -= MIN_YEAR;
		days++;
	}

	if ((static_cast<int>(year) - 28) > 400)
	{
		days -= (year - 28) / 400;
	}

	if ((static_cast<int>(year) - 28) > 100)
	{
		days += (year - 28) / 100;
	}

	days -= static_cast<unsigned>(year * EXACT_DAYS_IN_YEAR);
}