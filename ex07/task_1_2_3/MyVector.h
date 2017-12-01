#pragma once
#ifndef _MY_VEC_CONT
#define _MY_VEC_CONT
#include <iterator>
static constexpr unsigned defaultSize = 10;

template<typename IteratorType>
class RandomAccessIterator : public std::iterator<std::random_access_iterator_tag, IteratorType> {
public:
	RandomAccessIterator(IteratorType* ptr = nullptr) { m_ptr = ptr; }
	RandomAccessIterator(const RandomAccessIterator<IteratorType>& rawIterator) = default;
	~RandomAccessIterator() {}

	RandomAccessIterator<IteratorType>& operator=(const RandomAccessIterator<IteratorType>& rawIterator) = default;
	RandomAccessIterator<IteratorType>& operator=(IteratorType* ptr) {
		m_ptr = ptr;
		return (*this);
	}

	operator bool() const {
		if (m_ptr)
			return true;
		else
			return false;
	}

	bool operator==(const RandomAccessIterator<IteratorType>& rawIterator) const {
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator!=(const RandomAccessIterator<IteratorType>& rawIterator) const {
		return (m_ptr != rawIterator.getConstPtr());
	}

	RandomAccessIterator<IteratorType>& operator+=(const int& movement) {
		m_ptr += movement;
		return (*this);
	}
	RandomAccessIterator<IteratorType>& operator-=(const int& movement) {
		m_ptr -= movement;
		return (*this);
	}
	RandomAccessIterator<IteratorType>& operator++() {
		++m_ptr;
		return (*this);
	}
	RandomAccessIterator<IteratorType>& operator--() {
		--m_ptr;return (*this);
	}
	RandomAccessIterator<IteratorType> operator++(int) {
		auto temp(*this);
		++m_ptr;
		return temp;
	}
	RandomAccessIterator<IteratorType> operator--(int ) {
		auto temp(*this);
		--m_ptr;
		return temp;
	}
	RandomAccessIterator<IteratorType> operator+(const int& movement) {
		auto oldPtr = m_ptr;
		m_ptr += movement;
		auto temp(*this);
		m_ptr = oldPtr;
		return temp;
	}
	RandomAccessIterator<IteratorType> operator-(const int& movement) {
		auto oldPtr = m_ptr;
		m_ptr -= movement;
		auto temp(*this);
		m_ptr = oldPtr;
		return temp;
	}

	int operator-(const RandomAccessIterator<IteratorType>& rawIterator) {
		return std::distance(rawIterator.getPtr(), this->getPtr());
	}

	IteratorType& operator*() {
		return *m_ptr;
	}
	const IteratorType& operator*()const { 
		return *m_ptr;
	}
	IteratorType* operator->() {
		return m_ptr;
	}

	IteratorType* getPtr() const {
		return m_ptr;
	}
	const IteratorType* getConstPtr()const { 
		return m_ptr;
	}

protected:

	IteratorType* m_ptr;
};

template <typename T>
class MyVector {
	//members
	unsigned capacity;
	T* container;
	RandomAccessIterator<T> it;

public:
	using value_type = T;

	MyVector() : capacity(defaultSize), container(new T[capacity]), it(container) {}
	MyVector(unsigned n) : capacity(n), container(new T[capacity]), it(container) {}
	~MyVector() { delete[] container; }

	void push_back(const T& element) {
		if (it.getPtr() == container + capacity) resize(this->capacity * 2);
		*it = element;
		it++;
	}

	MyVector<T>& operator=(const MyVector<T>& other) {
		MyVector<T>& lhs = *this;
		lhs.clear();
		lhs.resize(other.capacity);
		std::copy(other.begin(), other.end(), std::back_inserter(lhs));
		return lhs;
	}

	void resize(unsigned n) {
		if (n <= capacity) return;
		//create tmp container which we fill with the values
		MyVector<T> newContainer(n);
		std::copy(this->begin(), this->end(), std::back_inserter(newContainer));
		//update members
		this->capacity = n;
		auto tmp = this->container;
		this->container = newContainer.container;
		this->it = newContainer.it;
		//to free old values simply set the new container pointer to the old ones 
		newContainer.container = tmp;
	}

	T& operator[](int index) {
		if (index >= capacity) throw 11;
		return container[index];
	}
	
	RandomAccessIterator<T> begin() const {
		return RandomAccessIterator<T>(container);
	}
	RandomAccessIterator<T> end() const {
		return it;
	}

	void clear() {
		it = container;
	}
};

#endif // !_MY_VEC_CONT
