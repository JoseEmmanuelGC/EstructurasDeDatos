#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "nodeException.h"

template<class T>
class Node {
    private:
        T* dataPtr;
        Node<T>* left;
        Node<T>* right;

    public:
        Node();
        Node(const T&);
        ~Node();

        T& getData();
        T* getDataPtr();
        Node<T>*& getLeft();
        Node<T>*& getRight();

        void setData(const T&);
        void setDataPtr(T*);
        void setRight(Node<T>*);
        void setLeft(Node<T>*);
    };

template<class T>
Node<T>::Node() {
    left = right = nullptr;
    dataPtr = nullptr;
    }

template<class T>
Node<T>::Node(const T& e) : Node() {
    dataPtr = new T(e);

    if(dataPtr == nullptr){
        throw NodeException("Memoria no disponible al inicializar nodo");
    }
    }

template<class T>
Node<T>::~Node() {
    delete dataPtr;
}

template<class T>
T& Node<T>::getData() {
    if(dataPtr == nullptr){
        throw NodeException("Dato no disponible en  getData del nodo");
    }
    return *dataPtr;
    }

template<class T>
T* Node<T>::getDataPtr() {
    return dataPtr;
    }

template<class T>
Node<T>*& Node<T>::getRight() {
    return right;
    }

template<class T>
Node<T>*& Node<T>::getLeft() {
    return left;
    }

template<class T>
void Node<T>::setData(const T& e) {
    if(dataPtr == nullptr){
        dataPtr = new T;
        if(dataPtr == nullptr){
            throw NodeException("Memoria no disponible en setData");
        }
    }
    *dataPtr = e;
    }

template<class T>
void Node<T>::setDataPtr(T* p) {
    dataPtr = p;
    }

template<class T>
void Node<T>::setRight(Node<T>* p) {
    right = p;
    }

template<class T>
void Node<T>::setLeft(Node<T>* p) {
    left = p;
    }

#endif // NODE_H_INCLUDED
