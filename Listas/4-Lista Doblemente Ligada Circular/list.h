#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "node.h"
#include "listException.h"

template<class T>
class List {
private:
    Node<T>* anchor;

    bool isValidPos(Node<T>*);

public:
    List();
    List(const List<T>&);
    ~List();

    bool isEmpty();

    void insertData(Node<T>*,const T&);
    void deleteData(Node<T>*);

    Node<T>* getFirstPos();
    Node<T>* getLastPos();
    Node<T>* getPrevPos(Node<T>*);
    Node<T>* getNextPos(Node<T>*);
    Node<T>* findData(const T&);

    T& retrive(Node<T>*);

    void printData();

    void deleteAll();
};

template<class T>
bool List<T>::isValidPos(Node<T>* p) {
    if(isEmpty())
        return false;

    Node<T>* aux = anchor;
    do {
        if(aux == p)
            return true;

        aux = aux->getNext();
    }
    while(aux != anchor);

    return false;
}
///***
template<class T>
List<T>::List()
{
    anchor = nullptr;
}

template<class T>
List<T>::List(const List<T>& l) : List() {
    if(isEmpty())
        return;

    Node<T>* aux = l.anchor;
    do {
        insertData(getLastPos(), aux->getData());

        aux = aux->getNext();
    }
    while(aux != l.anchor);
}

template<class T>
List<T>::~List()
{
    deleteAll();
}

template<class T>
bool List<T>::isEmpty()
{
    return anchor == nullptr;
}

template<class T>
void List<T>::insertData(Node<T>* p, const T& e)
{
    if(!isValidPos(p) and p != nullptr)
        throw ListException("Posicion invalida al tratar de insertar");

    Node<T>* aux = new Node<T>(e);

    if(aux == nullptr)
        throw ListException("Memoria no disponible al tratar de insertar");

    if(p == nullptr) {
        if(isEmpty()) {
            aux->setPrev(aux);
            aux->setNext(aux);
        } else {
            aux->setPrev(getLastPos());
            aux->setNext(anchor);

            getLastPos()->setNext(aux);
            anchor->setPrev(aux);
        }
        anchor = aux;
    } else {
        aux->setPrev(p);
        aux->setNext(p->getNext());

        p->getNext()->setPrev(aux);
        p->setNext(aux);
    }
}

template<class T>
void List<T>::deleteData(Node<T>* p)
{
    if(!isValidPos())
        throw ListException("Posicion invalida al tratar de eliminar");

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    if(p == anchor) {
        anchor = nullptr;
    }

    delete p;
}

template<class T>
Node<T>* List<T>::getFirstPos()
{
    return anchor;
}

template<class T>
Node<T>* List<T>::getLastPos()
{
    if(isEmpty())
        return nullptr;

    return anchor->getPrev();
}

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p)
{
    if(!isValidPos(p) or p == anchor)
        return nullptr;

    return p->getPrev();
}

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p)
{
    if(!isValidPos(p)or p == getLastPos())
        return nullptr;

    return p->getNext();
}

template<class T>
Node<T>* List<T>::findData(const T& e) {
    if(isEmpty())
        return nullptr;

    Node<T>* aux = anchor;
    do {
        if(aux->getData() == e)
            return aux;

        aux = aux->getNext();
    }
    while(aux != anchor);

    return nullptr;
}

template<class T>
T& List<T>::retrive(Node<T>* p)
{
    if(!isValidPos(p))
        throw ListException("Posicion invalida al hacer retrieve");

    return p->getData();
}

template<class T>
void List<T>::printData() {
    if(isEmpty())
        return;

    Node<T>* aux = anchor;
    do {
        std::cout << aux->getData().toString() << std::endl;

        aux = aux->getNext();
    }
    while(aux != anchor);
}

template<class T>
void List<T>::deleteAll() {
    if(isEmpty())
        return;

    Node<T>* mark = anchor;
    Node<T>* aux;

    do {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
    while(anchor != mark);

    anchor = nullptr;
}

#endif // LIST_H_INCLUDED
