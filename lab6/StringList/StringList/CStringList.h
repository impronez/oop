#pragma once
#include "stdafx.h"
#include <iterator>

class CStringList
{
private:
	struct Node;
	typedef std::shared_ptr<Node> NodeElem;
	typedef std::shared_ptr<const Node> ConstNodeElem;

public:

	class CIterator : public std::iterator<std::bidirectional_iterator_tag, Node>
	{
	public:
		CIterator()
			: m_ptr(nullptr) {}

		CIterator(NodeElem const& ptr)
			: m_ptr(ptr) {}

		bool operator==(CIterator const& it) const { return m_ptr == it.m_ptr; }

		bool operator!=(CIterator const& it) const { return m_ptr != it.m_ptr; }

		CIterator& operator++();

		CIterator operator++(int);

		CIterator& operator--();

		CIterator operator--(int);

		std::string& operator*() const;

	private:
		NodeElem m_ptr;

		friend class CStringList;
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
		
		std::string const& operator*() const;

	private:
		ConstNodeElem m_ptr;
	};

	typedef CIterator iterator;
	typedef CConstIterator const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const iterator> const_reverse_iterator;

	CStringList();
	
	~CStringList() = default;

	CStringList(const CStringList& list);

	CStringList(CStringList&& list) noexcept;

	CStringList& operator=(const CStringList& list);

	CStringList& operator=(CStringList&& list) noexcept;

	void PushFront(const std::string& str);

	void PushBack(const std::string& str);

	void Insert(iterator const& it, const std::string& str);

	void Delete(iterator const& it);

	void Clear();

	size_t GetSize() const;

	bool IsEmpty() const;

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
		Node(const std::string& initData, NodeElem const& initPrev, NodeElem const& initNext)
			: data(initData), prev(initPrev), next(initNext) {}
		~Node() = default;

		std::string data;
		NodeElem prev;
		NodeElem next;
	};

	size_t m_size;
	NodeElem m_pBegin;
	NodeElem m_pEnd;

	static NodeElem MakeNewElement();
	static NodeElem MakeNewElement(const std::string& data, const NodeElem& prev, const NodeElem& next);

};

