#ifndef STACK_H
#define STACK_H
#include "list.h"
template <typename T>
class stack : public list<T> {
public:
	stack();
	stack(const stack& aStack);
	void push(const T& data);
	void pop(const T& data);
};
//------------------------------------------------------------
template <typename T>
stack<T>::stack()
	: list<T>() {
}

template <typename T>
stack<T>::stack(const stack& aStack)
	: list<T>(aStack.first(), aStack.last()) {
}

template <typename T>
void stack<T>::push(const T& data) {
	stack<T>::push_front(data);
}
#endif	// STACK_H
