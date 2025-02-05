#include "generate_output.h"
#include "dll_node.h"
#include "doubly_linked_list.h"
#include <iostream>

void printList(DoublyLinkedList &list) {
    DllNode *curr = list.head;
    while (curr) {
        std::cout << curr->key << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

void reversePrintList(DoublyLinkedList &list) {
    DllNode *curr = list.tail;
    while (curr) {
        std::cout << curr->key << " ";
        curr = curr->prev;
    }
    std::cout << std::endl;
}