#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <exception>
#include <string>

class QueueException : public std::exception{
private:
    std::string msg;

public:
    explicit QueueException( const char* message ) : msg(message){ };

    explicit QueueException( const std::string message ) : msg( message){ }

    virtual ~QueueException() throw() {}

    virtual const char* what() const throw() { return msg.c_str(); }
    };

template<class T, int arraySize = 1024>
class Queue{
private:
    T data[arraySize];
    int frontPos;
    int endPos;

public:
    Queue();

    bool isEmpty();
    bool isFull();

    void enqueue(const T&);
    T dequeue();

    T getFront();
};

template<class T, int arraySize>
Queue<T,arraySize>::Queue(){
    frontPos = 0;
    endPos = arraySize - 1;
}

template<class T, int arraySize>
bool Queue<T,arraySize>::isEmpty(){
    return frontPos == endPos + 1 or
            (frontPos == 0 and endPos == arraySize - 1);
}

template<class T, int arraySize>
bool Queue<T,arraySize>::isFull(){
    return frontPos == endPos + 2 or
            (frontPos == 0 and endPos == arraySize - 2) or
                (frontPos == 1 and endPos == arraySize -1);
}

template<class T, int arraySize>
void Queue<T,arraySize>::enqueue(const T& e){
    if(isFull())
        throw QueueException("Desbordamiento de datos haciendo enqueue");

    if(++endPos == arraySize)
        endPos = 0;

    data[endPos] = e;
}

template<class T, int arraySize>
T Queue<T,arraySize>::dequeue(){
    if(isEmpty())
        throw QueueException("Insuficiencia de datos haciendo dequeue");

    T r=data[frontPos++];

    if(frontPos == arraySize)
        frontPos = 0;

    return r;
}

template<class T, int arraySize>
T Queue<T,arraySize>::getFront(){
    if(isEmpty())
        throw QueueException("Insuficiencia de datos haciendo getFront");

    return data[frontPos];
}

#endif // QUEUE_H_INCLUDED
