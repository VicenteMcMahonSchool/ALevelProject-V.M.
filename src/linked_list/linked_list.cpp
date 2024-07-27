#include "./linked_list.hpp"

// template <typename T>
// LinkedList<T>::~LinkedList()
// {
//     LinkedListNode<T> *current = this->head;
//     while (current)
//     {
//         LinkedListNode<T> *original = current;
//         current = current->next;
//         delete original;
//     }
// }

// template <typename T>
// void LinkedList<T>::add(T item)
// {
//     LinkedListNode<T> *newNode = new LinkedListNode<T>{.datum = item, .next = this->head};
//     this->head = newNode;
// }

void LinkedList::makeEmpty(void)
{
    LinkedListNode *current = this->head;
    while (current != NULL)
    {
        LinkedListNode *original = current;
        current = current->next;
        delete original;
    }
    this->head = NULL;
}

LinkedList::~LinkedList()
{
    makeEmpty();
}
void LinkedList::add(GameObject item)
{
    LinkedListNode *newNode = new LinkedListNode{.datum = item, .next = this->head};
    this->head = newNode;
}

// template class LinkedListNode<GameObject>;
// template class LinkedList<GameObject>;
