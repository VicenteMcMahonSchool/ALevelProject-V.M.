#pragma once
#include "../macros/macros.hpp"
#include "../rectangle/rectangle.hpp"

#define TRAVERSE(start, type, code)               \
    {                                             \
        LinkedListNode<type> *current = start;    \
        while (current)                           \
        {                                         \
            LinkedListNode<type> *item = current; \
            current = current->next;              \
            code;                                 \
        }                                         \
    }

template <typename T>
struct LinkedListNode
{
    T datum;
    LinkedListNode<T> *next = nullptr;
};

template <typename T>
struct LinkedList
{
    LinkedListNode<T> *head = nullptr;
    ~LinkedList();
    void add(T item);
};
