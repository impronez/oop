#include <iostream>
#include <array>

const int COUNT_OF_MONTHS = 12;

typedef std::array<int, COUNT_OF_MONTHS> DaysInMonths;

struct Date
{
    short year;
    short month;
    short day;
};

DaysInMonths CountDaysInMonths(const int year)
{
    DaysInMonths days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4) == 0)
    {
        days[1] += 1;
    }

    return days;
}

bool ParseDates(const Date* firstDate, const Date* secondDate, DaysInMonths& days)
{
    if (firstDate->year <= 0 || secondDate->year <= 0 || firstDate->year != secondDate->year)
    {
        return false;
    }

    if (firstDate->month <= 0 || secondDate->month <= 0
        || firstDate->month > 12 || secondDate->month > 12)
    {
        return false;
    }

    days = CountDaysInMonths(firstDate->year);
    
    if (firstDate->day <= 0 || secondDate->day <= 0 || firstDate->day > days[firstDate->month - 1]
        || secondDate->day > days[secondDate->month - 1])
    {
        return false;
    }

    return true;
}

int CountDaysBetweenMonths(const int differenceOfMonths, Date* firstDate,
    Date* secondDate, const DaysInMonths& days)
{
    Date* youngDate = firstDate;
    Date* lateDate = secondDate;
    
    if (differenceOfMonths > 0)
    {
        youngDate = secondDate;
        lateDate = firstDate;
    } 

    int countOfDays = 0;
    for (int i = youngDate->month; i < lateDate->month - 1; i++)
    {
        countOfDays += days[i];
    }
    return countOfDays;
}

bool IsTheSameWeekDays(Date* firstDate, Date* secondDate, const DaysInMonths& days)
{
    int differenceOfMonths = firstDate->month - secondDate->month;
    if (differenceOfMonths == 0 &&
        (abs(firstDate->day - secondDate->day) % 7) == 0)
    {
        return true;
    }
    
    int countOfDaysBetweenTwoDates = CountDaysBetweenMonths(differenceOfMonths, firstDate,
        secondDate, days);
    
    if ((countOfDaysBetweenTwoDates % 7) == 0)
    {
        return true;
    }

    return false;
}

int main()
{
    std::cout << "Enter 2 dates line by line in the format: 'YYYY MM DD'\n";
    Date* firstDate = new Date;
    Date* secondDate = new Date;
    DaysInMonths daysInMonths = {};
    std::cin >> firstDate->year >> firstDate->month >> firstDate->day
        >> secondDate->year >> secondDate->month >> secondDate->day;

    if (!ParseDates(firstDate, secondDate, daysInMonths))
    {
        std::cout << "ERROR\n";
        return 1;
    }
    
    if (IsTheSameWeekDays(firstDate, secondDate, daysInMonths))
    {
        std::cout << "Same week days\n";
    }
    else 
    {
        std::cout << "Different week days\n";
    }

    return 0;
}

/*
2023 2 2
2024 2 2

-2023 2 2
-2023 2 1

2024 2 2
2024 2 9

2024 3 1
2024 2 9

2024 1 5
2024 8 9

*/