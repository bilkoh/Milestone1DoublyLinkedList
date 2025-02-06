#include "doubly_linked_list.h"
#include <gtest/gtest.h>

class DoublyLinkedListTest : public ::testing::Test {
  protected:
    DoublyLinkedList list;

    void SetUp() override {
        // list starts empty
    }

    void TearDown() override { list.clear(); }
};
// Insert Tests
// --------------------
TEST_F(DoublyLinkedListTest, IsEmptyInitially) { EXPECT_TRUE(list.isEmpty()); }

TEST_F(DoublyLinkedListTest, InsertAtHeadSingle) {
    list.insertAtHead(10);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.head->key, 10);
    EXPECT_EQ(list.tail->key, 10);
    EXPECT_EQ(list.head, list.tail);
}

TEST_F(DoublyLinkedListTest, InsertAtHeadMultiple) {
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);
    EXPECT_EQ(list.head->key, 30);
    EXPECT_EQ(list.tail->key, 10);
}

TEST_F(DoublyLinkedListTest, InsertAtTailSingle) {
    list.insertAtTail(100);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.head->key, 100);
    EXPECT_EQ(list.tail->key, 100);
}

TEST_F(DoublyLinkedListTest, InsertAtTailMultiple) {
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    EXPECT_EQ(list.head->key, 10);
    EXPECT_EQ(list.tail->key, 30);
}

// remove Tests
// --------------------
TEST_F(DoublyLinkedListTest, RemoveFromEmpty) {
    list.remove(5);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveSingleNode) {
    list.insertAtHead(42);
    list.remove(42);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveMultipleNodes) {
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.remove(20);
    EXPECT_EQ(list.head->key, 10);
    EXPECT_EQ(list.tail->key, 30);
    list.remove(10);
    EXPECT_EQ(list.head->key, 30);
    EXPECT_EQ(list.tail->key, 30);
    list.remove(30);
    EXPECT_TRUE(list.isEmpty());
}

// removeHeaderNode Tests
// --------------------
TEST_F(DoublyLinkedListTest, RemoveHeaderNodeFromEmpty) {
    list.removeHeaderNode();
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveHeaderNodeSingle) {
    list.insertAtHead(5);
    list.removeHeaderNode();
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveHeaderNodeMultiple) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.removeHeaderNode();
    EXPECT_EQ(list.head->key, 2);
    EXPECT_EQ(list.tail->key, 3);
}

// removeTailNode Tests
// --------------------
TEST_F(DoublyLinkedListTest, RemoveTailNodeFromEmpty) {
    list.removeTailNode();
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveTailNodeSingle) {
    list.insertAtTail(5);
    list.removeTailNode();
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, RemoveTailNodeMultiple) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.removeTailNode();
    EXPECT_EQ(list.head->key, 1);
    EXPECT_EQ(list.tail->key, 2);
}

// findNode Tests
// --------------------
TEST_F(DoublyLinkedListTest, FindNodeInEmptyList) {
    EXPECT_EQ(list.findNode(1), nullptr);
}

TEST_F(DoublyLinkedListTest, FindNodeSingleElement) {
    list.insertAtHead(5);
    DllNode *node = list.findNode(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 5);
}

TEST_F(DoublyLinkedListTest, FindNodeMultipleElements) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);

    DllNode *node1 = list.findNode(1);
    ASSERT_NE(node1, nullptr);
    EXPECT_EQ(node1->key, 1);

    DllNode *node2 = list.findNode(2);
    ASSERT_NE(node2, nullptr);
    EXPECT_EQ(node2->key, 2);

    DllNode *node3 = list.findNode(3);
    ASSERT_NE(node3, nullptr);
    EXPECT_EQ(node3->key, 3);
}

TEST_F(DoublyLinkedListTest, FindNodeNonExistent) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);

    EXPECT_EQ(list.findNode(4), nullptr);
}

TEST_F(DoublyLinkedListTest, FindNodeAfterRemoval) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);

    list.removeHeaderNode(); // Removes node with key 1
    EXPECT_EQ(list.findNode(1), nullptr);

    list.removeTailNode(); // Removes node with key 3
    EXPECT_EQ(list.findNode(3), nullptr);

    DllNode *node = list.findNode(2);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 2);
}

// moveNodeToHead Tests
// --------------------
TEST_F(DoublyLinkedListTest, MoveNodeToHeadNotFound) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.moveNodeToHead(3);
    EXPECT_EQ(list.head->key, 1);
    EXPECT_EQ(list.tail->key, 2);
}

TEST_F(DoublyLinkedListTest, MoveNodeToHeadWhenAlreadyHead) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.moveNodeToHead(1);
    EXPECT_EQ(list.head->key, 1);
    EXPECT_EQ(list.tail->key, 2);
}

TEST_F(DoublyLinkedListTest, MoveNodeToHeadFromTail) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.moveNodeToHead(3);
    EXPECT_EQ(list.head->key, 3);
    EXPECT_EQ(list.tail->key, 2);
}

// moveNodeToTail Tests
// --------------------
TEST_F(DoublyLinkedListTest, MoveNodeToTailNotFound) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.moveNodeToTail(3);
    EXPECT_EQ(list.head->key, 1);
    EXPECT_EQ(list.tail->key, 2);
}

TEST_F(DoublyLinkedListTest, MoveNodeToTailWhenAlreadyTail) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.moveNodeToTail(2);
    EXPECT_EQ(list.head->key, 1);
    EXPECT_EQ(list.tail->key, 2);
}

TEST_F(DoublyLinkedListTest, MoveNodeToTailFromHead) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.moveNodeToTail(1);
    EXPECT_EQ(list.head->key, 2);
    EXPECT_EQ(list.tail->key, 1);
}

// Destructor/clear Tests
// --------------------
TEST_F(DoublyLinkedListTest, ClearEmptyList) {
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(DoublyLinkedListTest, ClearNonEmptyList) {
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}