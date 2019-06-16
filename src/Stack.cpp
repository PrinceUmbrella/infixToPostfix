
#include <iostream>
using namespace std;

// using the template feature to implement generic Stack.
//
// Stack is struct of an array and TOS information.
//       TOS indicates the index of the next empty location.
//       The elements are stacked from low-indexed
//       to high-indexed locations
//
// All basic set of STACK functions is O(1)

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
bool Stack<XType>::is_Empty()
{
    return ( TOS == 0 );
}

template <class XType>
bool Stack<XType>::is_Full()
{
    return ( TOS == MAX_SIZE );
}

template <class XType>
int Stack<XType>::getSize()
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
XType Stack<XType>::top()
{
    if (!this->is_Empty())
    {
        return (signStack[TOS - 1]);
    }
}





