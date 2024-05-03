#include "./linked_list.hpp"

template <typename T>
LinkedList<T>::~LinkedList()
{
    LinkedListNode<T> *current = this->head;
    while (current)
    {
        LinkedListNode<T> *original = current;
        current = current->next;
        delete original;
    }
}

template <typename T>
void LinkedList<T>::add(T item)
{
    LinkedListNode<T> *newNode = new LinkedListNode<T>{.datum = item, .next = this->head};
    this->head = newNode;
}

template class LinkedListNode<Rectangle>;
template class LinkedList<Rectangle>;
template class LinkedListNode<MovableRectangle>;
template class LinkedList<MovableRectangle>;
