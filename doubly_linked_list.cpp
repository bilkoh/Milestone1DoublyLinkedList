/**
*
* @author - Bilal Kohgadai
* @file doubly_linked_list.cpp -  My implementation of DLL.

01/27/2025 - initial creation

*/
#include "doubly_linked_list.h"
#include "dll_node.h"
#include "doubly_linked_list.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() { clear(); }

bool DoublyLinkedList::isEmpty() { return (head == nullptr); }

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

void DoublyLinkedList::remove(int key) {
  // TODO: Implement remove
  // TODO: Waiting to implement hash
  if (isEmpty())
    return;
}

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

void DoublyLinkedList::moveNodeToHead(int key) {
  // TODO: Implement moveNodeToHead
}

void DoublyLinkedList::moveNodeToTail(int key) {
  // TODO: Implement moveNodeToTail
}

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

DllNode *DoublyLinkedList::findNode(int key) {
  return node_map.count(key) ? node_map[key] : nullptr;
}