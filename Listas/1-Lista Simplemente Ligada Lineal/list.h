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
bool List<T>::isValidPos(Node<T>* p)
{
    Node<T>* aux = anchor;
    while(aux != nullptr){
        if(aux == p)
            return true;

        aux = aux->getNext();
    }

    return false;
}
///***
template<class T>
List<T>::List()
{
    anchor = nullptr;
}

template<class T>
List<T>::List(const List<T>& l) : List()
{
    Node<T>* aux = l.anchor;
    while(aux != nullptr){
        insertData(getLastPos(), aux->getData());

        aux = aux->getNext();
    }
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

    if(p == nullptr){
        aux->setNext(anchor);
        anchor = aux;
    }
    else{
        aux->setNext(p->getNext());
        p->setNext(aux);
    }
}

template<class T>
void List<T>::deleteData(Node<T>* p)
{
    if(!isValidPos())
        throw ListException("Posicion invalida al tratar de eliminar");

    if(p == anchor){ /// Eliminar el primero
        anchor = anchor->getNext();

    }
    else{ /// ELiminar del segundo en adelante
        getPrevPos(p)->setNext(p->getData());

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

    Node<T>* aux = anchor;
    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }
    return aux;

}

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p)
{
    if(isEmpty() or p == anchor)
        return nullptr;

    Node<T>* aux = anchor;
    while(aux->getNext() != p){
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p)
{
    if(!isValidPos(p))
        return nullptr;

    return p->getNext();
}

template<class T>
Node<T>* List<T>::findData(const T& e)
{
    Node<T>* aux = anchor;
    while(aux != nullptr){
        if(aux->getData() == e)
            return aux;

        aux = aux->getNext();
    }

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
void List<T>::printData()
{
    Node<T>* aux = anchor;
    while(aux != nullptr){
        std::cout << aux->getData().toString() << ", ";

        aux = aux->getNext();
    }
}

template<class T>
void List<T>::deleteAll()
{
    Node<T>* aux;

    while(anchor != nullptr){
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}


#endif // LIST_H_INCLUDED
