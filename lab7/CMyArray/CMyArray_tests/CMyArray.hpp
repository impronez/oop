#pragma once
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <initializer_list>
#include <iterator>

template <typename T>
class CMyArray
{
public:

	class CMyIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		CMyIterator()
			: m_ptr(nullptr) {}

		CMyIterator(T* const& ptr)
			: m_ptr(ptr) {}

		bool operator==(CMyIterator const& it) const { return m_ptr == it.m_ptr; }

		bool operator!=(CMyIterator const& it) const { return m_ptr != it.m_ptr; }

		T* operator->() const { return &m_ptr; }

		T& operator*() const { return *m_ptr; }

		T& operator[](std::ptrdiff_t offset) const
		{
			return &this;
		}

		T& operator+=(std::ptrdiff_t offset)
		{
			m_ptr += offset;
			return *this;
		}

		T& operator-=(std::ptrdiff_t offset)
		{
			m_ptr -= offset;
			return *this;
		}

		CMyIterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		CMyIterator operator++(int)
		{
			auto tmp(*this);
			++(*this);
			return tmp;
		}

		CMyIterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		CMyIterator operator--(int)
		{
			auto tmp(*this);
			--(*this);
			return tmp;
		}

	private:

		T* m_ptr;
	};

	typedef CMyIterator iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	iterator begin() { return iterator(&m_pItems[0]); }
	iterator end() { return iterator(&m_pItems[m_size]); }
	reverse_iterator rbegin() { return std::reverse_iterator<iterator>(end()); };
	reverse_iterator rend() { return std::reverse_iterator<iterator>(begin()); };

	CMyArray() = default;

	explicit CMyArray(size_t size)
		: m_pItems(new T[size]()), m_size(size), m_capacity(size) {}

	CMyArray(std::initializer_list<T> list)
		: m_pItems(new T[list.size()]()), m_size(list.size()), m_capacity(list.size())
	{
		try
		{
			std::copy(list.begin(), list.end(), m_pItems);
		}
		catch (...)
		{
			delete[] m_pItems;
			throw std::runtime_error("Error of copying!");
		}
	}

	~CMyArray()
	{
		delete[] m_pItems;
	}

	CMyArray(const CMyArray& other)
		: m_pItems(new T[other.m_size]), m_size(other.m_size), m_capacity(other.m_size)
	{
		try
		{
			std::copy(other.m_pItems, other.m_pItems - other.m_size, m_pItems);
		}
		catch (const std::exception& err)
		{
			delete[] m_pItems;
			throw std::runtime_error("Error of copying!");
		}
	}

	CMyArray(CMyArray&& other) noexcept
	{
		m_pItems = std::move(other.m_pItems);
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_size = 0;
	}

	CMyArray& operator=(const CMyArray& other)
	{
		if (this != other)
		{
			CMyArray copy(other);
			std::swap(m_pItems, other.m_pItems);
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
		}

		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (this != other)
		{
			m_pItems = std::move(other.m_pItems);
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			other.m_size = 0;
		}

		return *this;
	}

	void Push(const T& elem)
	{
		if (m_capacity <= m_size)
		{
			ResizeCapacity();
		}
		m_size++;
		m_pItems[m_size - 1] = elem;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	size_t GetCapacity() const
	{
		return m_capacity;
	}

	T& operator[](size_t index)
	{
		if (index > m_size - 1)
		{
			throw std::out_of_range("Index is out of range!");
		}

		return m_pItems[index];
	}


	void Resize(size_t size)
	{
		T* newPItems = new T[size]();
		try
		{
			std::copy_n(m_pItems, std::min(m_size, size), newPItems);
		}
		catch (...)
		{
			delete[] newPItems;
			throw std::runtime_error("Error copying!");
		}
		delete[] m_pItems;
		m_pItems = newPItems;

		m_capacity = size;
		m_size = size;
	}

	void Clear()
	{
		delete[] m_pItems;

		m_pItems = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

private:
	T* m_pItems = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;

	void ResizeCapacity()
	{
		m_capacity *= 2;
		T* newPItems = new T[m_capacity]();
		try
		{
			std::copy_n(m_pItems, m_size, newPItems);
		}
		catch (...)
		{
			delete[] newPItems;
			throw std::runtime_error("Error copying!");
		}
		delete[] m_pItems;
		m_pItems = newPItems;
	}
};
