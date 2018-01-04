#ifndef DLIST_H
#define DLIST_H
#include <iostream>
#include <cmath>
#include "node.h"
using std::cout;
using std::cerr;
using std::endl;
using std::abs;
template<typename T> class DList
{
private:
    Node<T>* ptrFirst;
    Node<T>* ptrLast;
    int lsize;
public:
    DList() : ptrFirst{nullptr}, ptrLast{nullptr}, lsize{0} { /*default constructor */}
    ~DList() {removeAll();}
    bool isEmpty() const;
    int size() const;
    T findMaxItem() const;
    T findMinItem() const;
    void findIndexOfItem(const T& data) const;
    void pushBack(const T& data);
    void pushFont(const T& data);
    T popBack();
    T popFont();
    void removeAt(int index);
    void insertAt(int index, T data);
    void printList() const;
    void printReverseList() const;
    void removeAll();
};

//-------------------------------------------------------------------------
template<typename T>
bool DList<T>::isEmpty() const
{
    if(ptrFirst == nullptr && ptrLast == nullptr)
        return true;
    return false;
}

template<typename T>
int DList<T>::size() const
{
    return lsize;
}

template<typename T>
T DList<T>::findMaxItem() const
{
    T maxItem{ptrFirst->data};
    Node<T>* tempNode{ptrFirst->ptrNext};
    while(tempNode != nullptr)
    {
        if (tempNode->data > maxItem)
            maxItem = tempNode->data;
        tempNode = tempNode->ptrNext;
    }
    return maxItem;
}

template<typename T>
T DList<T>::findMinItem() const
{
    T minItem{ptrFirst->data};
    Node<T>* tempNode{ptrFirst->ptrNext};
    while(tempNode != nullptr)
    {
        if (tempNode->data < minItem)
            minItem = tempNode->data;
        tempNode = tempNode->ptrNext;
    }
    return minItem;
}

template<typename T>
void DList<T>::findIndexOfItem(const T &data) const
{
    cout << data << " was found at : ";
    Node<T>* tempNode{ptrFirst};
    int currentIndex{};
    while(tempNode != nullptr)
    {
        if (tempNode->data == data)
            cout << currentIndex << " ";
        tempNode = tempNode->ptrNext;
        currentIndex++;
    }
}

template<typename T>
void DList<T>::pushBack(const T &data)
{
    if (isEmpty())
    {
        ptrFirst = ptrLast = new Node<T>{data, nullptr, nullptr};
    }
    else
    {
        Node<T>* newNode{new Node<T>{data, nullptr, ptrLast}};
        ptrLast->ptrNext = newNode;
        ptrLast = newNode;
    }
    lsize++;
}

template<typename T>
void DList<T>::pushFont(const T &data)
{
    if (isEmpty())
    {
        ptrFirst = ptrLast = new Node<T>{data, nullptr, nullptr};
    }
    else
    {
         Node<T>* newNode{new Node<T>{data, ptrFirst, nullptr}};
         ptrFirst->ptrPre = newNode;
         ptrFirst = newNode;
    }
    lsize++;
}

template<typename T>
T DList<T>::popBack()
{
    T removedData{ptrLast->data};
    if (lsize == 1)
    {
        delete ptrLast;
        ptrLast = ptrFirst = nullptr;
    }
    else
    {
        Node<T>* tempNode{ptrLast->ptrPre};
        ptrLast->ptrPre->ptrNext = nullptr;
        ptrLast->ptrPre = nullptr;
        delete ptrLast;
        ptrLast = tempNode;
    }
    lsize--;
    return removedData;
}

template<typename T>
T DList<T>::popFont()
{
    T removedData{ptrFirst->data};
    if (lsize == 1)
    {
        delete ptrFirst;
        ptrFirst = ptrLast = nullptr;
    }
    else
    {
        Node<T>* tempNode{ptrFirst->ptrNext};
        ptrFirst->ptrNext->ptrPre = nullptr;
        ptrFirst->ptrNext = nullptr;
        delete ptrFirst;
        ptrFirst = tempNode;
    }
    lsize--;
    return removedData;
}

template<typename T>
void DList<T>::removeAt(int index)
{
    if (index < 0 || index >= lsize)
        cerr << "Invalid index - Couldn't remove" << endl;
    else if (index == 0)
        popFont();
    else if (index == lsize - 1)
        popBack();
    else
    {
        Node<T>* tempNode{ptrFirst};
        int currentIndex{0};
        if (index <= lsize - index)
        {
            while(currentIndex < index - 1)
            {
                tempNode = tempNode->ptrNext;
                currentIndex++;
            }
        }
        else
        {
            tempNode = ptrLast->ptrPre;
            currentIndex = lsize - 2;
            while(currentIndex >= index)
            {
                tempNode = tempNode->ptrPre;
                currentIndex--;
            }
        }
        Node<T>* deletedNote{tempNode->ptrNext};
        tempNode->ptrNext = deletedNote->ptrNext;
        deletedNote->ptrNext->ptrPre = tempNode;
        deletedNote->ptrNext = deletedNote->ptrPre = nullptr;
        delete deletedNote;
        lsize--;
    }

}

template<typename T>
void DList<T>::insertAt(int index, T data)
{
    if (index <= 0)
        pushFont(data);
    else if (index >= lsize)
        pushBack(data);
    else
    {
        Node<T>* tempNode{ptrFirst};
        Node<T>* newNode{new Node<T>{data, nullptr, nullptr}};
        int currentIndex{0};
        if (index <= lsize - index)
        {
            while(currentIndex < index - 1)
            {
                tempNode = tempNode->ptrNext;
                currentIndex++;
            }
            tempNode->ptrNext->ptrPre = newNode;
            newNode->ptrNext = tempNode->ptrNext;
            tempNode->ptrNext = newNode;
            newNode->ptrPre = tempNode;
        }
        else
        {
            tempNode = ptrLast->ptrPre;
            currentIndex = lsize - 2;
            while(currentIndex >= index)
            {
                tempNode = tempNode->ptrPre;
                currentIndex--;
            }
            tempNode->ptrNext->ptrPre = newNode;
            newNode->ptrNext = tempNode->ptrNext;
            tempNode->ptrNext = newNode;
            newNode->ptrPre = tempNode;
        }
        lsize++;
    }

}

template<typename T>
void DList<T>::printList() const
{
    if (isEmpty())
        return;
    Node<T>* tempNode{ptrFirst};
    while(tempNode != nullptr)
    {
        cout << tempNode->data << " -> ";
        tempNode = tempNode->ptrNext;
    }
    cout << endl;
}

template<typename T>
void DList<T>::printReverseList() const
{
    if (isEmpty())
         return;
    Node<T>* tempNode{ptrLast};
    while (tempNode != nullptr)
    {
        cout << tempNode->data << " -> ";
        tempNode = tempNode->ptrPre;
    }
    cout << endl;
}

template<typename T>
void DList<T>::removeAll()
{
    if (isEmpty())
        return;
    cout << "Removing all data" << endl;
    while(ptrFirst != ptrLast)
    {
        Node<T>* tempNode{ptrFirst};
        ptrFirst = ptrFirst->ptrNext;
        delete tempNode;
    }
    delete ptrFirst;
    ptrFirst = ptrLast = nullptr;
}
#endif // DLIST_H


