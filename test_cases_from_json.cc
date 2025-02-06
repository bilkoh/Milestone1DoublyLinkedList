#include "doubly_linked_list.h"
#include <gtest/gtest.h>
#include <vector>

// Helper struct to expose the private head pointer for testing purposes.
struct TestAccessor : public DoublyLinkedList {
    using DoublyLinkedList::head; // allow access to head in tests
};

std::vector<int> traverseList(const DoublyLinkedList &dll) {
    std::vector<int> result;
    // Cast to TestAccessor to access head pointer
    const TestAccessor &accessor = reinterpret_cast<const TestAccessor &>(dll);
    for (DllNode *curr = accessor.head; curr != nullptr; curr = curr->next) {
        result.push_back(curr->key);
    }
    return result;
}

class DoublyLinkedListTest : public ::testing::Test {
  protected:
    DoublyLinkedList list;

    void SetUp() override {
        // list starts empty
    }

    void TearDown() override { list.clear(); }
};

TEST_F(DoublyLinkedListTest, TestCase1) {
    // testCase1 operations:
    // { "isEmpty": {} },
    // { "insertAtHead": 50 },
    // { "insertAtHead": 40 },
    // { "insertAtHead": 30 },
    // { "insertAtTail": 60 },
    // { "insertAtTail": 70 },
    // { "insertAtTail": 80 },
    // { "insertAtTail": 90 },
    // { "insertAtHead": 20 },
    // { "insertAtHead": 10 },
    // { "insertAtTail": 100 },
    // { "isEmpty": {} }
    EXPECT_TRUE(list.isEmpty());
    list.insertAtHead(50);
    list.insertAtHead(40);
    list.insertAtHead(30);
    list.insertAtTail(60);
    list.insertAtTail(70);
    list.insertAtTail(80);
    list.insertAtTail(90);
    list.insertAtHead(20);
    list.insertAtHead(10);
    list.insertAtTail(100);
    EXPECT_FALSE(list.isEmpty());

    std::vector<int> expected = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    EXPECT_EQ(traverseList(list), expected);
}

TEST_F(DoublyLinkedListTest, TestCase2) {
    // testCase2 operations:
    // { "isEmpty": {} },
    // { "insertAtHead": 30 },
    // { "remove": 30 },
    // { "insertAtTail": 40 },
    // { "insertAtHead": 50 },
    // { "insertAtTail": 70 },
    // { "insertAtHead": 80 },
    // { "insertAtHead": 1000 },
    // { "remove": 70 },
    // { "isEmpty": {} }
    EXPECT_TRUE(list.isEmpty());
    list.insertAtHead(30);
    list.remove(30);
    list.insertAtTail(40);
    list.insertAtHead(50);
    list.insertAtTail(70);
    list.insertAtHead(80);
    list.insertAtHead(1000);
    list.remove(70);
    EXPECT_FALSE(list.isEmpty());

    std::vector<int> expected = {1000, 80, 50, 40};
    EXPECT_EQ(traverseList(list), expected);
}

TEST_F(DoublyLinkedListTest, TestCase3) {
    // testCase3 operations:
    // { "isEmpty": {} },
    // { "insertAtHead": 80 },
    // { "remove": 30 },
    // { "insertAtTail": 40 },
    // { "insertAtHead": 50 },
    // { "removeHeaderNode": {} },
    // { "insertAtTail": 70 },
    // { "insertAtHead": 180 },
    // { "insertAtHead": 1000 },
    // { "removeTailNode": {} },
    // { "remove": 50 },
    // { "isEmpty": {} }
    EXPECT_TRUE(list.isEmpty());
    list.insertAtHead(80);
    list.remove(30); // no-op
    list.insertAtTail(40);
    list.insertAtHead(50);
    list.removeHeaderNode(); // removes 50
    list.insertAtTail(70);
    list.insertAtHead(180);
    list.insertAtHead(1000);
    list.removeTailNode(); // removes tail (70)
    list.remove(50);       // no-op, 50 already removed
    EXPECT_FALSE(list.isEmpty());

    std::vector<int> expected = {1000, 180, 80, 40};
    EXPECT_EQ(traverseList(list), expected);
}

TEST_F(DoublyLinkedListTest, TestCase4) {
    // testCase4 operations:
    // { "isEmpty": {} },
    // { "insertAtHead": 10 },
    // { "moveNodeToTail": 10 },
    // { "insertAtTail": 40 },
    // { "insertAtHead": 50 },
    // { "moveNodeToTail": 50 },
    // { "insertAtTail": 70 },
    // { "moveNodeToHead": 70 },
    // { "insertAtHead": 180 },
    // { "insertAtHead": 1000 },
    // { "removeTailNode": {} },
    // { "remove": 180 },
    // { "insertAtHead": 100 },
    // { "insertAtHead": 10000 },
    // { "removeHeaderNode": {} },
    // { "isEmpty": {} }
    EXPECT_TRUE(list.isEmpty());
    list.insertAtHead(10);    // list: 10
    list.moveNodeToTail(10);  // list still: 10
    list.insertAtTail(40);    // list: 10,40
    list.insertAtHead(50);    // list: 50,10,40
    list.moveNodeToTail(50);  // move 50 => list: 10,40,50
    list.insertAtTail(70);    // list: 10,40,50,70
    list.moveNodeToHead(70);  // list: 70,10,40,50
    list.insertAtHead(180);   // list: 180,70,10,40,50
    list.insertAtHead(1000);  // list: 1000,180,70,10,40,50
    list.removeTailNode();    // removes 50, list: 1000,180,70,10,40
    list.remove(180);         // list: 1000,70,10,40
    list.insertAtHead(100);   // list: 100,1000,70,10,40
    list.insertAtHead(10000); // list: 10000,100,1000,70,10,40
    list.removeHeaderNode();  // removes 10000, list: 100,1000,70,10,40
    EXPECT_FALSE(list.isEmpty());

    std::vector<int> expected = {100, 1000, 70, 10, 40};
    EXPECT_EQ(traverseList(list), expected);
}

TEST_F(DoublyLinkedListTest, TestCase5) {
    // testCase5 operations:
    // { "isEmpty": {} },
    // { "insertAtHead": 10 },
    // { "insertAtTail": 10000 },
    // { "moveNodeToTail": 50 },
    // { "insertAtHead": 1000 },
    // { "insertAtTail": 50 },
    // { "insertAtTail": 70 },
    // { "removeHeaderNode": {} },
    // { "removeTailNode": {} },
    // { "insertAtHead": 80 },
    // { "moveNodeToTail": 50 },
    // { "moveNodeToHead": 44 },
    // { "remove": 90 },
    // { "insertAtHead": 88 }
    EXPECT_TRUE(list.isEmpty());
    list.insertAtHead(10);    // list: 10
    list.insertAtTail(10000); // list: 10,10000
    list.moveNodeToTail(50);  // 50 not found; no change
    list.insertAtHead(1000);  // list: 1000,10,10000
    list.insertAtTail(50);    // list: 1000,10,10000,50
    list.insertAtTail(70);    // list: 1000,10,10000,50,70
    list.removeHeaderNode();  // removes 1000; list: 10,10000,50,70
    list.removeTailNode();    // removes 70; list: 10,10000,50
    list.insertAtHead(80);    // list: 80,10,10000,50
    list.moveNodeToTail(50);  // 50 is already tail; list unchanged
    list.moveNodeToHead(44);  // 44 not found; no change
    list.remove(90);          // 90 not found; no change
    list.insertAtHead(88);    // list: 88,80,10,10000,50

    std::vector<int> expected = {88, 80, 10, 10000, 50};
    EXPECT_EQ(traverseList(list), expected);
}