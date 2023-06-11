#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <typeinfo>
#include "node.h"
template <typename T>
class list {
protected:
	node<T>* pFirst;
	node<T>* pLast;
	size_t lsize;

public:
	explicit list(node<T>* initHead = nullptr, node<T>* initTail = nullptr);
	list(const list& srcList);
	list& operator=(const list& srcList) = delete;	// just forget the assignment operator
	virtual ~list();

	bool isEmpty() const;
	size_t size() const {
		return lsize;
	}
	const T& at(size_t index) const;
	const T& first() const {
		return pFirst->data;
	}
	const T& last() const {
		return pLast->data;
	}
	T& operator[](size_t index) const;
	bool contains(const T& value) const;
	void push_back(const T& data);
	void push_front(const T& data);
	void insert_at(int index, const T& data);
	void clear();
};
//--------------------------------------------------------------------------------
template <typename T>
list<T>::list(node<T>* initHead, node<T>* initTail)
	: pFirst{initHead}
	, pLast{initTail}
	, lsize{0} {
	cout << "Calling list DEFAULT CONSTRUCTOR <" << typeid(T).name() << ">" << endl;
}

template <typename T>
list<T>::list(const list& srcList)
	: list(srcList.pFirst, srcList.pLast) {
	//
}

template <typename T>
list<T>::~list() {
	clear();
}

template <typename T>
bool list<T>::isEmpty() const {
	if (pFirst == nullptr || pLast == nullptr)
		return true;
	return false;
}

template <typename T>
const T& list<T>::at(size_t index) const {
	try {
		if (index >= lsize)
			throw "your index is invalid\a";
		node<T>* tempNode{pFirst};
		size_t currentIndex{0};
		while (tempNode->nextNode != nullptr && currentIndex != index) {
			tempNode = tempNode->nextNode;
			currentIndex++;
		}
		return tempNode->data;
	} catch (const char* error) {
		cout << error << endl;
		exit(1);
	}
}

template <typename T>
T& list<T>::operator[](size_t index) const {
	try {
		if (index >= lsize)
			throw "your index is invalid\a";
		node<T>* tempNode{pFirst};
		size_t currentIndex{0};
		while (tempNode->nextNode != nullptr && currentIndex != index) {
			tempNode = tempNode->nextNode;
			currentIndex++;
		}
		return tempNode->data;
	} catch (const char* error) {
		cout << error << endl;
		exit(1);
	}
}

template <typename T>
bool list<T>::contains(const T& value) const {
	if (isEmpty())
		return false;
	else {
		node<T>* tempNode{pFirst};
		while (tempNode != nullptr) {
			if (tempNode->data == value)
				return true;
			tempNode = tempNode->nextNode;
		}
	}
	return false;
}

template <typename T>
void list<T>::push_back(const T& data) {
	node<T>* newNode{new node<T>{data, nullptr}};
	if (isEmpty())
		pFirst = pLast = newNode;
	else {
		pLast->nextNode = newNode;
		pLast = newNode;
	}
	lsize++;
}

template <typename T>
void list<T>::push_front(const T& data) {
	node<T>* newNode{new node<T>{data, nullptr}};
	if (isEmpty())
		pFirst = pLast = newNode;
	else {
		newNode->nextNode = pFirst;
		pFirst = newNode;
	}
	lsize++;
}

template <typename T>
void list<T>::insert_at(int index, const T& data) {
	node<T>* newNode{new node<T>{data, nullptr}};
	if (index <= 0)
		push_front(newNode);
	else if (index >= lsize)
		push_back(newNode);
	else {
		node<T>* tempNode{pFirst};
		int currentIndex{0};
		while (currentIndex < index - 1) {
			currentIndex++;
			tempNode = tempNode->nextNode;
		}
		newNode->nextNode = tempNode->nextNode;
		tempNode->nextNode = newNode;
		lsize++;
	}
}

template <typename T>
void list<T>::clear() {
	if (isEmpty())
		return;
	while (pFirst != pLast) {
		node<T>* tempNode{pFirst};
		pFirst = pFirst->nextNode;
		delete tempNode;
	}
	delete pFirst;
	pFirst = pLast = nullptr;
}

#endif	// LIST_H
