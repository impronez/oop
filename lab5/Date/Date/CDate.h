#include "stdafx.h"
// ћес€ц
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// ƒень недели
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// ƒата в формате день-мес€ц-год. √од в диапазоне от 1970 до 9999
class CDate
{
public:
    // инициализируем дату заданными днем, мес€цем и годом.
    // примечание: год >= 1970
    CDate(unsigned day, Month month, unsigned year);

    // инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
    // например, 2 = 3 €нвар€ 1970, 32 = 2 феврал€ 1970 года и т.д.
    explicit CDate(unsigned timestamp);

    //  онструктор по умолчанию. —оздаЄт дату, равную 1 €нвар€ 1970.
    CDate() {};
    // TODO: {} to default

    // возвращает день мес€ца (от 1 до 31)
    unsigned GetDay() const;

    // возвращает мес€ц
    Month GetMonth() const;

    // возвращает год
    unsigned GetYear() const;

    // возвращает день недели
    WeekDay GetWeekDay() const;

    unsigned GetDaysNum() const
    {
        return m_days;
    }

    CDate& operator++();
    
    CDate operator++(int);

    CDate& operator--();

    CDate operator--(int);

    CDate operator+(int days) const;

    CDate operator-(int days) const;

    int operator-(const CDate& date) const;

    CDate& operator+=(int days);

    CDate& operator-=(int days);

    friend std::ostream& operator<<(std::ostream& stream, const CDate& date);

    friend std::istream& operator>>(std::istream& input, CDate& date);

    bool operator==(const CDate& date) const;

    bool operator!=(const CDate& date) const;

    bool operator<(const CDate& date) const;

    bool operator>(const CDate& date) const;

    bool operator<=(const CDate& date) const;

    bool operator>=(const CDate& date) const;

private:
    unsigned m_days = 0;

    static const unsigned MAX_DAYS_COUNT;

    static const std::map<Month, unsigned> DAYS_IN_MONTHS;

    static const std::map<unsigned, Month> DAYS_AFTER_EVERY_MONTH;

    static const std::map<unsigned, Month> DAYS_AFTER_EVERY_MONTH_IN_LEAP_YEAR;

    static bool IsLeapYear(unsigned year);

    static bool IsCorrectDayForMonth(unsigned day, Month month, bool isLeapYear);

    static unsigned CountTimestamp(unsigned day, Month currentMonth, unsigned year);

    static Month GetMonthByDays(const unsigned days, const std::map<unsigned, Month>& map);

    static unsigned GetDayByCountOfDays(unsigned days, const std::map<unsigned, Month>& map);

    static void DaysCounting(unsigned& days, unsigned year);
};

CDate operator+(int days, const CDate& date);