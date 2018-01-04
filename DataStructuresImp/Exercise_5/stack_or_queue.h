#ifndef STACK_OR_QUEUE_H
#define STACK_OR_QUEUE_H
#include "node.h"
template<typename T>
class stack_or_queue
{
protected:
    node<T>* pFisrt;
    node<T>* pLast;
    int lsize;
public:
    stack_or_queue();
    virtual ~stack_or_queue();

    bool isEmpty() const;
    int size() const
    {
        return lsize;
    }
    const T& at(int index) const;
    const T& first() const;
    const T& last() const;
    T& operator[](int index) const;
    T pop();
    bool contains(const T& value) const;
    //void insert_at(int index, node<T> *newNode);
    void removeAll();

};
//--------------------------------------------------------------------------------
template<typename T>
stack_or_queue<T>::stack_or_queue()
    : pFisrt{nullptr}, pLast{nullptr}, lsize{0}
{

}

template<typename T>
stack_or_queue<T>::~stack_or_queue()
{
    removeAll();
}

template<typename T>
bool stack_or_queue<T>::isEmpty() const
{
    return (pFisrt == nullptr || pLast == nullptr);
}

template<typename T>
const T &stack_or_queue<T>::at(int index) const
{
    try
    {
        if (index >= lsize) throw "your index is invalid\a";
        node<T>* tempNode{pFisrt};
        int currentIndex{0};
        while(tempNode->ptrNext != nullptr && currentIndex != index)
        {
            tempNode = tempNode->ptrNext;
            currentIndex++;
        }
        return tempNode->data;
    }
    catch(const char* error)
    {
        cout << error << endl;
        exit(1);
    }
}

template<typename T>
const T &stack_or_queue<T>::first() const
{
    return pFisrt->data;
}

template<typename T>
const T &stack_or_queue<T>::last() const
{
    return pLast->data;
}

template<typename T>
T &stack_or_queue<T>::operator[](int index) const
{
    try
    {
        if (index >= lsize) throw "your index is invalid\a";
        node<T>* tempNode{pFisrt};
        size_t currentIndex{0};
        while(tempNode->ptrNext != nullptr && currentIndex != index)
        {
            tempNode = tempNode->ptrNext;
            currentIndex++;
        }
        return tempNode->data;
    }
    catch(const char* error)
    {
        cout << error << endl;
        exit(1);
    }
}

template<typename T>
T stack_or_queue<T>::pop()
{
    T removedData{pFisrt->data};
    node<T>* removedNode{pFisrt};
    pFisrt = pFisrt->ptrNext;
    delete removedNode;
    lsize--;
    return removedData;
}

template<typename T>
bool stack_or_queue<T>::contains(const T &value) const
{
    if (isEmpty())
        return false;
    else
    {
        node<T>* tempNode{pFisrt};
        while(tempNode != nullptr)
        {
            if (tempNode->data == value)
                return true;
            tempNode = tempNode->ptrNext;
        }
    }
    return false;
}

//template<typename T>
/*void stack_or_queue<T>::insert_at(int index, node<T> *newNode)
{
    if (index <= 0)
        push_front(newNode);
    else if (index >= lsize)
        push_back(newNode);
    else
    {
        node<T>* tempNode{pFisrt};
        int currentIndex{0};
        while(currentIndex < index - 1)
        {
            currentIndex++;
            tempNode = tempNode->ptrNext;
        }
        newNode->ptrNext = tempNode->ptrNext;
        tempNode->ptrNext = newNode;
        lsize++;
    }
}*/

template<typename T>
void stack_or_queue<T>::removeAll()
{
    if (isEmpty())
        return;
    cout << "Removing all data" << endl;
    while(pFisrt != pLast)
    {
        node<T>* tempNode{pFisrt};
        pFisrt = pFisrt->ptrNext;
        delete tempNode;
    }
    delete pFisrt;
    pFisrt = pLast = nullptr;
}

#endif // STACK_OR_QUEUE_H
