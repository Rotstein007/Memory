#include "LinkedList.h"

ListNode::ListNode(int value) : value(value), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

void LinkedList::add(int value) {
    auto newNode = std::make_unique<ListNode>(value);
    if (!head) {
        head = std::move(newNode);
        tail = head.get();
    } else {
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
}