#ifndef QSTACK_H
#define QSTACK_H
#include "stack_or_queue.h"
template<typename T>
class qstack : public stack_or_queue<T>
{
public:
    qstack();
    void push(T data);
};


template<typename T>
qstack<T>::qstack()
    : stack_or_queue<T>()
{

}

template<typename T>
void qstack<T>::push(T data)
{
    node<T>* newNode {new node<T>{data, nullptr}};
    if (this->isEmpty())
        this->pFisrt = this->pLast = newNode;
    else
    {
        newNode->ptrNext = this->pFisrt;
        this->pFisrt = newNode;
    }
    this->lsize++;
}
#endif // QSTACK_H


