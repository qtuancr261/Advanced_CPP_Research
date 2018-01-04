#ifndef NODE_H
#define NODE_H

template<typename T> struct Node
{
    T data;
    Node* ptrNext;
    Node* ptrPre;
};
#endif // NODE_H
