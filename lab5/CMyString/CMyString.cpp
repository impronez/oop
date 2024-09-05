#include "CMyString.h"

char CMyString::s_zeroChar = '\0';
const size_t CMyString::s_defaultCapacity = 15;

int CMyString::CompareCMyStrings(const CMyString& str1, const CMyString& str2)
{
	size_t minLength = std::min(str1.GetLength(), str2.GetLength());
	int compareResult = std::memcmp(str1.GetStringData(), str2.GetStringData(), minLength);

	if (compareResult == 0)
	{
		if (str1.GetLength() < str2.GetLength())
		{
			return -1;
		}
		else if (str1.GetLength() > str2.GetLength())
		{
			return 1;
		}
	}

	return compareResult;
}

size_t CMyString::SetCapacity(size_t length)
{
	size_t capacity = s_defaultCapacity;
	while (capacity < length)
	{
		capacity *= 2;
	}
	return capacity;
}

CMyString CMyString::StringsConcatenation(const char* firstPChars, size_t firstLength,
	const char* secondPChars, size_t secondLength)
{
	size_t resultLength = firstLength + secondLength;
	size_t capacity = CMyString::SetCapacity(resultLength);
	char* result = new char[capacity + 1];

	std::memcpy(result, firstPChars, firstLength);
	std::memcpy(result + firstLength, secondPChars, secondLength);
	result[resultLength] = CMyString::s_zeroChar;

	CMyString str(std::move(result), resultLength);
	delete[] result;
	return str;
}

CMyString::CMyString()
{
	m_capacity = s_defaultCapacity;
	m_pChars = new char[m_capacity + 1];
	m_pChars[0] = s_zeroChar;
	m_length = 0;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, pString != nullptr ? std::strlen(pString) : 0)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		length = 0;
	}

	m_capacity = SetCapacity(length);
	m_pChars = new char[m_capacity + 1];
	m_length = length;
	if (length != 0)
	{
		std::memcpy(m_pChars, pString, length);
	}
	m_pChars[length] = s_zeroChar;
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_pChars, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_pChars = other.m_pChars;
	m_length = other.m_length;
	m_capacity = other.m_capacity;

	other.Clear();
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	if (m_pChars != &s_zeroChar)
	{
		delete[] m_pChars;
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pChars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("Index out of acceptable range!");
	}

	if (!m_pChars)
	{
		return CMyString();
	}

	return CMyString(m_pChars + start, length);
}

void CMyString::Clear()
{
	if (m_capacity != s_defaultCapacity)
	{
		m_capacity = s_defaultCapacity;
	}

	if (m_pChars != nullptr)
	{
		m_pChars = nullptr;
		delete[] m_pChars;
		m_pChars = new char[m_capacity + 1];
	}

	m_pChars = &s_zeroChar;
	m_length = 0;
}

size_t CMyString::GetCapacity()
{
	return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString copy(other);
		std::swap(m_pChars, copy.m_pChars);
		std::swap(m_length, copy.m_length);
		std::swap(m_capacity, copy.m_capacity);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		m_pChars = other.m_pChars;
		m_length = other.m_length;
		m_capacity = other.m_capacity;

		other.Clear();
	}

	return *this;
}

CMyString CMyString::operator+(const CMyString& other)
{
	return StringsConcatenation(m_pChars, m_length, other.m_pChars, other.m_length);
}

CMyString CMyString::operator+(const std::string& stlStr)
{
	return StringsConcatenation(m_pChars, m_length, stlStr.c_str(), stlStr.length());
}

CMyString operator+(const std::string& stlStr, const CMyString& myStr)
{
	return CMyString::StringsConcatenation(stlStr.c_str(), stlStr.length(),
		myStr.GetStringData(), myStr.GetLength());
}

CMyString CMyString::operator+(const char* pString)
{
	return StringsConcatenation(m_pChars, m_length, pString, std::strlen(pString));
}

CMyString operator+(const char* pString, const CMyString& myStr)
{
	return CMyString::StringsConcatenation(pString, std::strlen(pString),
		myStr.GetStringData(), myStr.GetLength());
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	return *this = *this + other;
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::out_of_range("Index out of range!");
	}

	return *(m_pChars + index);
}

char& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::out_of_range("Index out of range!");
	}

	return *(m_pChars + index);
}

bool CMyString::operator==(const CMyString& other) const
{
	if (m_length != other.m_length)
	{
		return false;
	}

	return std::memcmp(m_pChars, other.m_pChars, m_length) == 0;
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(std::memcmp(m_pChars, other.m_pChars, m_length) == 0);
}

bool CMyString::operator<(const CMyString& other) const
{
	return CompareCMyStrings(*this, other) < 0;
}

bool CMyString::operator>(const CMyString& other) const
{
	return CompareCMyStrings(*this, other) > 0;
}

bool CMyString::operator<=(const CMyString& other) const
{
	return CompareCMyStrings(*this, other) <= 0;
}

bool CMyString::operator>=(const CMyString& other) const
{
	return CompareCMyStrings(*this, other) >= 0;
}

std::ostream& operator<<(std::ostream& ostream, const CMyString& str)
{
	for (size_t i = 0; i < str.m_length; ++i)
	{
		ostream << str[i];
	}

	return ostream;
}

std::istream& operator>>(std::istream& istream, CMyString& str)
{
	std::string inputStr;
	istream >> inputStr;
	str = inputStr;

	return istream;
}