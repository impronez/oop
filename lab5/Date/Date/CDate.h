#include "stdafx.h"
// �����
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// ���� ������
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// ���� � ������� ����-�����-���. ��� � ��������� �� 1970 �� 9999
class CDate
{
public:
    // �������������� ���� ��������� ����, ������� � �����.
    // ����������: ��� >= 1970
    CDate(unsigned day, Month month, unsigned year);

    // �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
    // ��������, 2 = 3 ������ 1970, 32 = 2 ������� 1970 ���� � �.�.
    explicit CDate(unsigned timestamp);

    // ����������� �� ���������. ������ ����, ������ 1 ������ 1970.
    CDate() {};
    // TODO: {} to default

    // ���������� ���� ������ (�� 1 �� 31)
    unsigned GetDay() const;

    // ���������� �����
    Month GetMonth() const;

    // ���������� ���
    unsigned GetYear() const;

    // ���������� ���� ������
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