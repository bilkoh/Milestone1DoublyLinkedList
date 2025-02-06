/**
 * @file generate_output.cpp
 * @author Bilal Kohgadai
 * @brief helper functions for printing out DoublyLinkedList
 * @version 0.1
 * @date 2025-02-05
 *
 * @copyright Copyright (c) 2025
 *
 */
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