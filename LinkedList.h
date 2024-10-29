#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>

class ListNode {
public:
    int value;
    std::unique_ptr<ListNode> next;

    explicit ListNode(int value);
};

class LinkedList {
public:
    std::unique_ptr<ListNode> head;
    ListNode* tail;

    LinkedList();
    void add(int value);
};

#endif