#ifndef NODE_H
#define NODE_H
#include <iostream>
using std::cout;
using std::endl;
template <typename T>
struct node {
	T data;
	node* nextNode;
};

#endif	// NODE_H
