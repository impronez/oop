#pragma once
#include "stdafx.h"
#include <iterator>

template<typename T>
class CMyList
{
private:
	struct Node;
	typedef std::shared_ptr<Node> NodeElem;
	typedef std::shared_ptr<const Node> ConstNodeElem;

public:

	class CIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		CIterator()
			: m_ptr(nullptr) {}

		CIterator(NodeElem const& ptr)
			: m_ptr(ptr) {}

		bool operator==(CIterator const& it) const { return m_ptr == it.m_ptr; }

		bool operator!=(CIterator const& it) const { return m_ptr != it.m_ptr; }


	private:
		T* m_ptr;
	};

	class CConstIterator : public std::iterator<std::bidirectional_iterator_tag, Node>
	{
	public:
		CConstIterator() {};

		CConstIterator(ConstNodeElem const& ptr)
			: m_ptr(ptr) {}

		bool operator==(CConstIterator const& it) const { return m_ptr == it.m_ptr; }

		bool operator!=(CConstIterator const& it) const { return m_ptr != it.m_ptr; }

		CConstIterator& operator++();

		CConstIterator operator++(int);

		CConstIterator& operator--();

		CConstIterator operator--(int);

		T const& operator*() const;

	private:
		ConstNodeElem m_ptr;
	};

	typedef CIterator iterator;
	typedef CConstIterator const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	CMyList();

	~CMyList() = default;

	CMyList(const CMyList& list);

	CMyList(CMyList&& list) noexcept;

	CMyList& operator=(const CMyList& list);

	CMyList& operator=(CMyList&& list) noexcept;

	void Insert(iterator const& it, const std::string& str);

	void Delete(iterator const& it);

	size_t GetSize() const;

	iterator begin();

	iterator end();

	CConstIterator begin() const;

	CConstIterator end() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

private:

	struct Node
	{
		Node() {}
		Node(const T& initData, NodeElem const& initPrev, NodeElem const& initNext)
			: data(initData), prev(initPrev), next(initNext) {}
		~Node() = default;

		T data;
		NodeElem prev;
		NodeElem next;
	};

	size_t m_size;
	NodeElem m_pBegin;
	NodeElem m_pEnd;

	static NodeElem MakeNewElement();
	static NodeElem MakeNewElement(T& data, const NodeElem& prev, const NodeElem& next);
};

template<typename T>
inline CMyList<T>::NodeElem CMyList<T>::MakeNewElement()
{
	return std::make_shared<Node>();
}

template<typename T>
inline CMyList<T>::NodeElem CMyList<T>::MakeNewElement(T& data, const NodeElem& prev, const NodeElem& next)
{
	return std::make_shared<Node>(data, prev, next);
}

template<typename T>
inline CMyList<T>::CMyList()
{
	m_pEnd = MakeNewElement();
	m_pBegin = m_pEnd;
	m_size = 0;
}

template<typename T>
inline CMyList<T>::CMyList(const CMyList& list)
{
	m_size = list.m_size;
	m_pBegin = MakeNewElement(list.m_pBegin->data, nullptr, nullptr);
	NodeElem prevTmp = m_pBegin;
	NodeElem ptrCopyTmp = list.m_pBegin->next;

	while (ptrCopyTmp != list.m_pEnd)
	{
		NodeElem tmp = MakeNewElement(ptrCopyTmp->data, prevTmp, nullptr);
		prevTmp->next = tmp;
		prevTmp = tmp;
		ptrCopyTmp = ptrCopyTmp->next;
	}
	m_pEnd = MakeNewElement(list.m_pEnd->data, prevTmp, nullptr);
	prevTmp->next = m_pEnd;
}

template<typename T>
inline CMyList<T>::CMyList(CMyList&& list) noexcept
{
	m_pBegin = std::move(list.m_pBegin);
	m_pEnd = std::move(list.m_pEnd);
	m_size = std::move(list.m_size);

	list.m_size = 0;
}

template<typename T>
inline CMyList<T>& CMyList<T>::operator=(const CMyList& list)
{
	if (this != &list)
	{
		CStringList copy(list);
		std::swap(m_size, copy.m_size);
		std::swap(m_pBegin, copy.m_pBegin);
		std::swap(m_pEnd, copy.m_pEnd);
	}

	return *this;
}

template<typename T>
inline CMyList<T>& CMyList<T>::operator=(CMyList&& list) noexcept
{
	if (this != &list)
	{
		m_pBegin = std::move(list.m_pBegin);
		m_pEnd = std::move(list.m_pEnd);
		m_size = std::move(list.m_size);

		list.m_size = 0;
	}

	return *this;
}

template<typename T>
inline void CMyList<T>::Insert(iterator const& it, const std::string& str)
{
	NodeElem elem = MakeNewElement(str, nullptr, it.m_ptr);
	if (it.m_ptr != m_pBegin)
	{
		it.m_ptr->prev->next = elem;
		elem->prev = it.m_ptr->prev;
	}
	else
	{
		m_pBegin = elem;
	}
	it.m_ptr->prev = elem;
	m_size++;
}

template<typename T>
inline void CMyList<T>::Delete(iterator const& it)
{
	if (it != m_pEnd)
	{
		it.m_ptr->next->prev = it.m_ptr->prev;
		if (it == m_pBegin)
		{
			m_pBegin = it.m_ptr->next;
		}
		else
		{
			it.m_ptr->prev->next = it.m_ptr->next;
		}
	}
	m_size--;
}

template<typename T>
inline size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template<typename T>
inline CMyList<T>::iterator CMyList<T>::begin()
{
	return iterator();
}

template<typename T>
inline CMyList<T>::iterator CMyList<T>::end()
{
	return iterator();
}

template<typename T>
inline CMyList<T>::const_iterator CMyList<T>::begin() const
{
	return CConstIterator();
}

template<typename T>
inline CMyList<T>::const_iterator CMyList<T>::end() const
{
	return CConstIterator();
}

template<typename T>
inline reverse_iterator CMyList<T>::rbegin()
{
	return reverse_iterator();
}

template<typename T>
inline reverse_iterator CMyList<T>::rend()
{
	return reverse_iterator();
}




