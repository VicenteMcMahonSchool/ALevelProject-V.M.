#pragma once
#include "../macros/macros.hpp"
#include "../game_objects/game_object/game_object.hpp"

// #define TRAVERSE(start, type, code)               \
//     {                                             \
//         LinkedListNode<type> *current = start;    \
//         while (current)                           \
//         {                                         \
//             LinkedListNode<type> *item = current; \
//             current = current->next;              \
//             code;                                 \
//         }                                         \
//     }

#define TRAVERSE(start, type, code)         \
    {                                       \
        LinkedListNode *current = start;    \
        while (current)                     \
        {                                   \
            LinkedListNode *item = current; \
            current = current->next;        \
            code;                           \
        }                                   \
    }

struct LinkedListNode
{
    GameObject datum;
    LinkedListNode *next = nullptr;
};

struct LinkedList
{
    LinkedListNode *head = nullptr;
    void add(GameObject item);
    ~LinkedList();
};