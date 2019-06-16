#ifndef STACK_H
#define STACK_H
#include <iostream>
static const int MAX_SIZE = 80;
using namespace std;

template <class XType>
class Stack
{
    public:
        Stack();
        ~Stack();
        bool is_Empty() const;
        bool is_Full() const;
        void push(XType item);
        void pop();
        XType top() const;
        int getSize() const;

    private:
        XType signStack[ MAX_SIZE ];
        int TOS;
};

template <class XType>
Stack<XType>::Stack()
{
    TOS = 0;
}

template <class XType>
Stack<XType>::~Stack()
{
    TOS = 0;
}

template <class XType>
bool Stack<XType>::is_Empty() const
{
    return ( TOS == 0 );
}

template <class XType>
bool Stack<XType>::is_Full() const
{
    return ( TOS == MAX_SIZE );
}

template <class XType>
int Stack<XType>::getSize() const
{
    return (TOS);
}

template <class XType>
void Stack<XType>::push(XType item)
{
    if (!this->is_Full())
    {
        signStack[TOS] = item;
        TOS++;
    }
}

template <class XType>
void Stack<XType>::pop()
{
    if (!this->is_Empty())
    {
        --TOS;
    }
}

template <class XType>
XType Stack<XType>::top() const
{
    if (!this->is_Empty())
    {
        return (signStack[TOS - 1]);
    }
    else
    {
        cout << "No Top" << endl;
        return (0);
    }
}

#endif // STACK_H
