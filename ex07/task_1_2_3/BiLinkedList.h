#pragma once
#ifndef _MY_LINKED_LIST
#define _MY_LINKED_LIST
#include <iterator>
#include <memory>

template<typename IteratorType>
class BidirecIterator : public std::iterator<std::bidirectional_iterator_tag, IteratorType> {
public:
	BidirecIterator(IteratorType* ptr = nullptr) : prev_ptr(nullptr) { current_ptr = ptr; }
	BidirecIterator(IteratorType* ptr, IteratorType* _prev) { current_ptr = ptr; prev_ptr = _prev; }
	BidirecIterator(const BidirecIterator<IteratorType>& rawIterator) = default;
	~BidirecIterator() {}

	BidirecIterator<IteratorType>& operator=(const BidirecIterator<IteratorType>& rawIterator) = default;
	BidirecIterator<IteratorType>& operator=(IteratorType* ptr) {
		current_ptr = ptr;
		if (current_ptr) prev_ptr = current_ptr->prev;
		return (*this);
	}

	operator bool() const {
		if (current_ptr)
			return true;
		else
			return false;
	}

	bool operator==(const BidirecIterator<IteratorType>& rawIterator) const {
		return (current_ptr == rawIterator.current_ptr && prev_ptr == rawIterator.prev_ptr);
	}

	bool operator!=(const BidirecIterator<IteratorType>& rawIterator) const {
		return (current_ptr != rawIterator.current_ptr && prev_ptr != rawIterator.prev_ptr);
	}

	BidirecIterator<IteratorType>& operator++() {
		prev_ptr = current_ptr;
		current_ptr = current_ptr->Next();
		return (*this);
	}

	BidirecIterator<IteratorType>& operator--() {
		current_ptr = prev_ptr;
		prev_ptr = current_ptr->Prev();
		return (*this);
	}

	BidirecIterator<IteratorType> operator++(ptrdiff_t) {
		auto temp(*this);
		prev_ptr = current_ptr;
		current_ptr = current_ptr->Next();
		return temp;
	}

	BidirecIterator<IteratorType> operator--(ptrdiff_t) {
		auto temp(*this);
		current_ptr = prev_ptr;
		prev_ptr = current_ptr->Prev();
		return temp;
	}

	IteratorType& operator*() {
		return *current_ptr;
	}
	const IteratorType& operator*() const {
		return *current_ptr;
	}
	IteratorType* operator->() {
		return current_ptr;
	}

	IteratorType* getPtr() const {
		return current_ptr;
	}
	const IteratorType* getConstPtr() const {
		return current_ptr;
	}

protected:
	//this structor will keep trac of the end
	//e.g. end of linked list is current_ptr = nullptr
	//and prev_prt = valid address
	IteratorType* current_ptr;
	IteratorType* prev_ptr;
};

template <typename T>
class MyBidirecListNode {
	T elemt;
	std::shared_ptr<MyBidirecListNode<T>> next;
	MyBidirecListNode<T>* prev;

	void insertAfter(MyBidirecListNode<T>* head, std::shared_ptr<MyBidirecListNode<T>> toInsert) {
		toInsert->prev = head;
		toInsert->next = head->next;
		if (head->next) { head->next->prev = toInsert.get(); }
		head->next = toInsert;
	}
public:
	using value_type = typename T;

	MyBidirecListNode(T element) { elemt = element; }
	~MyBidirecListNode() {}

	void push_front(T element) {
		auto beg = this->begin();
		std::shared_ptr<MyBidirecListNode<T>> insertBlock {new MyBidirecListNode<T>{beg->elemt}};
		beg->elemt = element;
		insertAfter(beg.getPtr(), insertBlock);
	}

	void push_back(T element) {

	}

	BidirecIterator<MyBidirecListNode<T>> begin() {
		MyBidirecListNode<T>* tmp = this;
		while (tmp->prev != nullptr) { tmp = tmp->prev; }
		return BidirecIterator<MyBidirecListNode<T>>{tmp};
	}

	BidirecIterator<MyBidirecListNode<T>> end() {
		MyBidirecListNode<T>* tmp = this;
		while (tmp->next) { tmp = tmp->next.get(); }
		return BidirecIterator<MyBidirecListNode<T>>{nullptr, tmp};
	}

	T GetVal() {
		return elemt;
	}

	MyBidirecListNode<T>* Next() {
		return this->next.get();
	}

	MyBidirecListNode<T>* Prev() {
		return this->prev;
	}
};

#endif // !_MY_LINKED_LIST