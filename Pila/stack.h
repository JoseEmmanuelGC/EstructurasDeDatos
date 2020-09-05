#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <exception>
#include <string>
#include <iostream>

class StackException : public std::exception {
    private:
        std::string msg;

    public:
        explicit StackException( const char* message ) : msg(message) { };

        explicit StackException( const std::string message ) : msg( message) { }

        virtual ~StackException() throw() {}

        virtual const char* what() const throw() {
            return msg.c_str();
            }
    };

template<class T, int arraySize = 1024>
class Stack {
    private:
        T data[arraySize];
        int top;

    public:
        Stack();

        bool isEmpty();
        bool isFull();

        void push(const T&);
        T pop();

        T getTop();
    };

template<class T,int arraySize>
Stack<T,arraySize>::Stack() {
    top=-1;
    }

template<class T,int arraySize>
bool Stack<T,arraySize>::isEmpty() {
    return top==-1;
    }

template<class T,int arraySize>
bool Stack<T,arraySize>::isFull() {
    return top==arraySize-1;
    }

template<class T,int arraySize>
void Stack<T,arraySize>::push(const T& e) {
    if(isFull())
        throw StackException("Desbordamiento de datos al tratar de apilar");
    data[++top]=e;
    }

template<class T,int arraySize>
T Stack<T,arraySize>::pop() {
    if(isEmpty())
        throw StackException("Insuficiencia de datos tratando de desapilar");

    return data[top--];
    }

template<class T,int arraySize>
T Stack<T,arraySize>::getTop() {
    if(isEmpty())
        throw StackException("Insuficiencia de datos al hacer Top");
    return data[top];
    }

#endif // STACK_H_INCLUDED
