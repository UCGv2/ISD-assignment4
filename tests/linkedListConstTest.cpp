// @author G. Hemingway, copyright 2018 - All rights reserved
//
#include "LinkedList.h"
#include <gtest/gtest.h>

namespace {

// Sample data
const int DATA[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const size_t LEN = 10;

// The fixture for testing ConstLinkedListIterator.
class ConstLinkedListIteratorTest : public ::testing::Test {
};

TEST_F(ConstLinkedListIteratorTest, BeginAndDereference)
{
    // Create a populated linked-list
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);
    const LinkedList<int> b(a);

    // Simple begin test
    LinkedList<int>::const_iterator i = b.begin();
    const auto j = b.begin();
    EXPECT_TRUE(i == j);
    EXPECT_FALSE(i != j);
    EXPECT_EQ(*i, *j);
}

TEST_F(ConstLinkedListIteratorTest, IncrementDecrement)
{
    // Create a populated linked-list
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);
    const LinkedList<int> b(a);

    auto i = b.begin();
    auto j = b.begin();
    i++;
    EXPECT_FALSE(i == j);
    i--;
    EXPECT_TRUE(i == j);
    ++i;
    EXPECT_FALSE(i == j);
    --i;
    EXPECT_TRUE(i == j);
}

TEST_F(ConstLinkedListIteratorTest, End)
{
    // Create a populated linked-list
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);
    const LinkedList<int> b(a);

    auto i = b.begin();
    uint32_t count = 0;
    for (; i != b.end(); ++i) {
        count++;
    }
    EXPECT_EQ(count, LEN);
}

TEST_F(ConstLinkedListIteratorTest, Arrows)
{
    LinkedList<std::string> list;
    list.add("the");
    list.add("quick");
    list.add("brown");
    list.add("fox");
    list.add("jumped");
    list.add("over");
    list.add("the");
    list.add("lazy");
    list.add("dog");
    const LinkedList<std::string> constList(list);

    size_t index = 0;
    size_t lengths[9] = { 3, 5, 5, 3, 6, 4, 3, 4, 3 };
    for (auto iter = constList.begin(); iter != constList.end(); ++iter) {
        EXPECT_EQ(iter->length(), lengths[index++]);
    }
}

TEST_F(ConstLinkedListIteratorTest, Test1)
{
}

TEST_F(ConstLinkedListIteratorTest, Test2)
{
}

TEST_F(ConstLinkedListIteratorTest, Test3)
{
}

TEST_F(ConstLinkedListIteratorTest, Test4)
{
}

TEST_F(ConstLinkedListIteratorTest, Test5)
{
}

TEST_F(ConstLinkedListIteratorTest, Test6)
{
}
}
