#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template<class T>
class Node
{
private:
    T data;
    Node<T>* prev;
    Node<T>* next;

public:
    Node();
    Node(const T&);

    T& getData();
    Node<T>* getNext();
    Node<T>* getPrev();

    void setData(const T&);
    void setNext(Node<T>*);
    void setPrev(Node<T>*);
};

template<class T>
Node<T>::Node()
{
    prev = next = nullptr;
}

template<class T>
Node<T>::Node(const T& e) : Node()
{
    data = e;
}

template<class T>
T& Node<T>::getData()
{
    return data;
}

template<class T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template<class T>
Node<T>* Node<T>::getPrev()
{
    return prev;
}

template<class T>
void Node<T>::setData(const T& e)
{
    data = e;
}

template<class T>
void Node<T>::setNext(Node<T>* p)
{
    next = p;
}

template<class T>
void Node<T>::setPrev(Node<T>* p)
{
    prev = p;
}

#endif // NODE_H_INCLUDED
