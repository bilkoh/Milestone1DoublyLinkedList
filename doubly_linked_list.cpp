/**
 *
 * @author - Bilal Kohgadai
 * @file doubly_linked_list.cpp -  My implementation of DLL.
 * @date 01/27/2025
 * @brief Implementation of the DoublyLinkedList class.
 * @see doubly_linked_list.h
 * @see dll_node.h
 *
 * This file contains the implementation of the DoublyLinkedList class, which
 * provides a doubly linked list data structure.
 *
 */
#include "doubly_linked_list.h"
#include "dll_node.h"
#include "doubly_linked_list.h"

/**
 * @brief Constructs a new DoublyLinkedList object.
 *
 * This constructor initializes an empty doubly linked list by setting
 * both the head and tail pointers to nullptr.
 */
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

/**
 * @brief Doubly Linked List object
 *
 */
DoublyLinkedList::~DoublyLinkedList() { clear(); }

/**
 *
 * isEmpty
 *
 * Method to check if the list is empty
 *
 * @param    nothing
 *
 * @return   true if head pointer is nullptr, otherwise return false
 */
bool DoublyLinkedList::isEmpty() { return (head == nullptr); }

/**
 *
 * insertAtHead
 *
 * Method to insert a new node at the head of the list
 *
 * @param key    key for node to insert
 *
 * @return       nothing; updates doubly linked list and size
 */
void DoublyLinkedList::insertAtHead(int key) {
  DllNode *newNode = new DllNode(key);
  node_map[key] = newNode;

  if (head == nullptr) {
    head = tail = newNode;

  } else {
    DllNode *oldHead = head;
    newNode->next = oldHead;
    oldHead->prev = newNode;
    head = newNode;
  }
}

/**
 *
 * insertAtTail
 *
 * Method to insert a new node at the tail of the list
 *
 * @param key    key for node to insert
 *
 * @return       nothing; updates doubly linked list and size
 */
void DoublyLinkedList::insertAtTail(int key) {
  DllNode *newNode = new DllNode(key);
  node_map[key] = newNode;

  if (head == nullptr) {
    head = tail = newNode;

  } else {
    DllNode *oldTail = tail;
    oldTail->next = newNode;
    newNode->prev = oldTail;
    tail = newNode;
  }
}

/**
 *
 * remove
 *
 * Method to remove a node with a specific value from the list
 *
 * @param key    key for node to insert
 *
 * @return       nothing; updates doubly linked list
 */
void DoublyLinkedList::remove(int key) {
  if (isEmpty())
    return;

  DllNode *node = findNode(key);

  if (node == nullptr)
    return;

  // Case: node is only node in list
  // Case: node is head or tail
  if (node == head) {
    removeHeaderNode();
  } else if (node == tail) {
    removeTailNode();
  } else {
    // Case: removing from middle
    DllNode *prevNode = node->prev;
    DllNode *nextNode = node->next;

    if (prevNode)
      prevNode->next = nextNode;

    if (nextNode)
      nextNode->prev = prevNode;

    node_map.erase(key);
    delete node;
  }
}

/**
 *
 * removeHeaderNode
 *
 * Method to remove the header node (first node)
 *
 * @param        none
 *
 * @return       nothing; updates doubly linked list
 */
void DoublyLinkedList::removeHeaderNode() {
  if (isEmpty())
    return;

  DllNode *oldHead = head;
  head = head->next;

  if (head == nullptr)
    tail = nullptr; // ensure they're both null to signify empty
  else
    head->prev = nullptr;

  node_map.erase(oldHead->key);
  delete oldHead;
}

/**
 *
 * removeTailNode
 *
 * Method to remove the tail node (last node)
 *
 * @param        none
 *
 * @return       nothing; updates doubly linked list
 */
void DoublyLinkedList::removeTailNode() {
  if (isEmpty())
    return;

  DllNode *oldTail = tail;
  tail = tail->prev;

  if (tail == nullptr)
    head = nullptr; // ensure they're both null to signify empty
  else
    tail->next = nullptr; //

  node_map.erase(oldTail->key);
  delete oldTail;
}

/**
 *
 * moveNodeToHead
 *
 * Method to move a specific node to the head of the list
 *
 * @param key    key for node to move
 *
 * @return       nothing; updates doubly linked list
 */
void DoublyLinkedList::moveNodeToHead(int key) {
  if (isEmpty())
    return;

  DllNode *node = findNode(key);

  if (node == nullptr || node == head)
    return;

  // reposition next and prev pointers
  if (node == tail) {
    // Case: moving tail to head
    tail = tail->prev;
    if (tail)
      // Case: avoid issues w/ only one node in list
      tail->next = nullptr;

  } else {
    // Case: moving a middle node
    DllNode *prevNode = node->prev;
    DllNode *nextNode = node->next;
    if (prevNode)
      prevNode->next = nextNode;

    if (nextNode)
      nextNode->prev = prevNode;
  }

  // insertion
  node->prev = nullptr;
  node->next = head;

  if (!head) {
    // if empty list
    head = tail = node;

  } else {
    head->prev = node;
    head = node;
  }
}

/**
 *
 * moveNodeToTail
 *
 * Method to move a specific node to the tail of the list
 *
 * @param key    key for node to move
 *
 * @return       nothing; updates doubly linked list
 */
void DoublyLinkedList::moveNodeToTail(int key) {
  if (isEmpty())
    return;

  DllNode *node = findNode(key);

  if (node == nullptr || node == tail)
    return;

  // reposition next and prev pointers
  if (node == head) {
    // Case moving head to tail
    head = head->next;
    if (head)
      head->prev = nullptr;

  } else {
    // Case: moving a middle node
    DllNode *prevNode = node->prev;
    DllNode *nextNode = node->next;
    if (prevNode)
      prevNode->next = nextNode;

    if (nextNode)
      nextNode->prev = prevNode;
  }

  // insertion
  node->next = nullptr;
  node->prev = tail;

  if (!tail) {
    // if empty list
    head = tail = node;

  } else {
    tail->next = node;
    tail = node;
  }
}

/**
 *
 * clear
 *
 * Method to clear the list by deleting all nodes
 *
 * @param        none
 *
 * @return       nothing; reset size to 0
 */
void DoublyLinkedList::clear() {
  DllNode *curr = head;

  while (curr) {
    DllNode *temp = curr;
    curr = curr->next;
    delete temp;
  }

  head = tail = nullptr;
  node_map.clear();
}

/**
 *
 * findNode
 *
 * Method to find a node with a specific key
 *
 * @param key    key for node to find
 *
 * @return       pointer to the node if found, otherwise nullptr
 */
DllNode *DoublyLinkedList::findNode(int key) {
  return node_map.count(key) ? node_map[key] : nullptr;
}