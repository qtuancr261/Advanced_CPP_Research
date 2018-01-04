#ifndef QQUEUE_H
#define QQUEUE_H
#include "stack_or_queue.h"
template<typename T> class qqueue : public stack_or_queue<T>
{
public:
    qqueue();
    void insert(T data);
};


template<typename T>
qqueue<T>::qqueue()
    : stack_or_queue<T>()
{

}

template<typename T>
void qqueue<T>::insert(T data)
{
    node<T>* newNode{new node<T>{data, nullptr}};
    if (this->isEmpty())
        this->pFisrt = this->pLast = newNode;
    else
    {
        this->pLast->ptrNext = newNode;
        this->pLast = newNode;
    }
    this->lsize++;
}
#endif // QQUEUE_H
