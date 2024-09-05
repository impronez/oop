#pragma once
#include "stdafx.h"


class CMyString
{
public:
    // конструктор по умолчанию
    CMyString();

    // конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
    CMyString(const char* pString);


    // конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
    CMyString(const char* pString, size_t length);

    // конструктор копирования
    CMyString(CMyString const& other);

    // перемещающий конструктор
    // реализуется совместно с перемещающим оператором присваивания 
    CMyString(CMyString&& other) noexcept;

    // конструктор, инициализирующий строку данными из 
    // строки стандартной библиотеки C++
    CMyString(std::string const& stlString);

    // деструктор класса - освобождает память, занимаемую символами строки
    ~CMyString();

    // возвращает длину строки (без учета завершающего нулевого символа)
    size_t GetLength()const;

    // возвращает указатель на массив символов строки.
    // В конце массива обязательно должен быть завершающий нулевой символ
    // даже если строка пустая 
    const char* GetStringData()const;

    // возвращает подстроку с заданной позиции длиной не больше length символов
    CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

    // очистка строки (строка становится снова нулевой длины)
    void Clear();

    // Возвращает вместимость строки
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