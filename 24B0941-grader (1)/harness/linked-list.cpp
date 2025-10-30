// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE
// ************************************************************

#include "linked-list.h"
#include <iostream>
LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::push_back(int value)
{
    auto node = new ListNode(value);
    if (!head)
    {
        head = tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}


void LinkedList::clear()
{
    while (head)
    {
        auto tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr; 
}

void LinkedList::print() const
{
    for (auto p = head; p; p = p->next)
    {
        std::cout << p->data << (p->next ? " " : "\n");
    }
    if (!head) std::cout << "\n";
}

