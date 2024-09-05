#pragma once
#include "stdafx.h"


class CMyString
{
public:
    // ����������� �� ���������
    CMyString();

    // �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
    CMyString(const char* pString);


    // �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
    CMyString(const char* pString, size_t length);

    // ����������� �����������
    CMyString(CMyString const& other);

    // ������������ �����������
    // ����������� ��������� � ������������ ���������� ������������ 
    CMyString(CMyString&& other) noexcept;

    // �����������, ���������������� ������ ������� �� 
    // ������ ����������� ���������� C++
    CMyString(std::string const& stlString);

    // ���������� ������ - ����������� ������, ���������� ��������� ������
    ~CMyString();

    // ���������� ����� ������ (��� ����� ������������ �������� �������)
    size_t GetLength()const;

    // ���������� ��������� �� ������ �������� ������.
    // � ����� ������� ����������� ������ ���� ����������� ������� ������
    // ���� ���� ������ ������ 
    const char* GetStringData()const;

    // ���������� ��������� � �������� ������� ������ �� ������ length ��������
    CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

    // ������� ������ (������ ���������� ����� ������� �����)
    void Clear();

    // ���������� ����������� ������
    size_t GetCapacity();

    CMyString& operator=(const CMyString& other);

    CMyString& operator=(CMyString&& other) noexcept;

    CMyString operator+(const CMyString& other);

    CMyString operator+(const std::string& stlStr);

    CMyString operator+(const char* pString);

    CMyString& operator+=(CMyString const& other);

    friend CMyString operator+(const std::string& stlStr, const CMyString& myStr);

    friend CMyString operator+(const char* pString, const CMyString& myStr);

    char& operator[](size_t index);

    char& operator[](size_t index) const;

    bool operator==(const CMyString& other) const;

    bool operator!=(const CMyString& other) const;

    bool operator<(const CMyString& other) const;

    bool operator>(const CMyString& other) const;

    bool operator<=(const CMyString& other) const;

    bool operator>=(const CMyString& other) const;

    friend std::ostream& operator<<(std::ostream& ostream, const CMyString& str);

    friend std::istream& operator>>(std::istream& istream, CMyString& str);

    static char s_zeroChar;

    static const size_t s_defaultCapacity;

private:
    char* m_pChars;
    size_t m_length;
    size_t m_capacity; 

    static int CompareCMyStrings(const CMyString& str1, const CMyString& str2);

    static size_t SetCapacity(size_t length);

    static CMyString StringsConcatenation(const char* firstPChars, size_t firstLength,
        const char* secondPChars, size_t secondLength);
};