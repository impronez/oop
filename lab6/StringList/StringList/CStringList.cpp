#include "CStringList.h"

CStringList::NodeElem CStringList::MakeNewElement()
{
	return std::make_shared<Node>();
}

CStringList::NodeElem CStringList::MakeNewElement(const std::string& data, const NodeElem& prev, const NodeElem& next)
{
	return std::make_shared<Node>(data, prev, next);
}


CStringList::CStringList()
{
	m_pEnd = MakeNewElement();
	m_pBegin = m_pEnd;
	m_size = 0;
}

CStringList::CStringList(const CStringList& list)
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

CStringList::CStringList(CStringList&& list) noexcept
{
	m_pBegin = std::move(list.m_pBegin);
	m_pEnd = std::move(list.m_pEnd);
	m_size = std::move(list.m_size);
	
	list.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& list)
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

CStringList& CStringList::operator=(CStringList&& list) noexcept
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

void CStringList::PushFront(const std::string& str)
{
	NodeElem tmp = MakeNewElement(str, nullptr, m_pBegin);

	m_pBegin->prev = tmp;
	m_pBegin = tmp;
	m_size++;
}

void CStringList::PushBack(const std::string& str)
{
	NodeElem tmp = MakeNewElement(str, nullptr, m_pEnd);

	if (CStringList::IsEmpty())
	{
		m_pBegin = tmp;
	}
	else
	{
		m_pEnd->prev->next = tmp;
		tmp->prev = m_pEnd->prev;
	}
	m_pEnd->prev = tmp;
	m_size++;
}

void CStringList::Insert(iterator const& it, const std::string& str)
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

void CStringList::Delete(iterator const& it)
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

void CStringList::Clear()
{
	if (m_pBegin == m_pEnd)
	{
		return;
	}

	for (iterator it = m_pBegin; it != m_pEnd; ++it)
	{
		if (it != m_pBegin)
		{
			it.m_ptr->prev->next = nullptr;
			it.m_ptr->prev = nullptr;
		}
	}
	m_pEnd->prev = nullptr;
	m_pBegin = m_pEnd;

	m_size = 0;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

//iterators

CStringList::CIterator& CStringList::CIterator::operator++()
{
	assert(m_ptr->next);
	if (m_ptr)
	{
		m_ptr = m_ptr->next;
	}
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	assert(m_ptr->next);
	CIterator copy = *this;
	++(*this);
	return copy;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	assert(m_ptr->prev);
	if (m_ptr)
	{
		m_ptr = m_ptr->prev;
	}
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator--(int)
{
	assert(m_ptr->prev);
	CIterator copy = *this;
	--(*this);
	return copy;
}

std::string& CStringList::CIterator::operator*() const
{
	return m_ptr->data;
}

//const iterators

CStringList::CConstIterator& CStringList::CConstIterator::operator++()
{
	assert(m_ptr->next);
	if (m_ptr)
	{
		m_ptr = m_ptr->next;
	}
	return *this;
}

CStringList::CConstIterator CStringList::CConstIterator::operator++(int)
{
	assert(m_ptr->next);
	CConstIterator copy = *this;
	++(*this);
	return copy;
}

CStringList::CConstIterator& CStringList::CConstIterator::operator--()
{
	assert(m_ptr->prev);
	if (m_ptr)
	{
		m_ptr = m_ptr->prev;
	}
	return *this;
}

CStringList::CConstIterator CStringList::CConstIterator::operator--(int)
{
	assert(m_ptr->prev);
	CConstIterator copy = *this;
	--(*this);
	return copy;
}

std::string const& CStringList::CConstIterator::operator*() const
{
	return m_ptr->data;
}

//CStringList iterators

CStringList::iterator CStringList::begin()
{
	return iterator(m_pBegin);
}

CStringList::CConstIterator CStringList::begin() const
{
	return CConstIterator(m_pBegin);
}

CStringList::iterator CStringList::end()
{
	return iterator(m_pEnd);
}

CStringList::CConstIterator CStringList::end() const
{
	return CConstIterator(m_pEnd);
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return reverse_iterator(m_pEnd);
}

CStringList::reverse_iterator CStringList::rend()
{
	return reverse_iterator(m_pBegin);
}
