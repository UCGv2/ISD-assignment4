// @author G. Hemingway, copyright 2018 - All rights reserved
//
#include "LinkedList.h"
#include <gtest/gtest.h>

namespace {

// Sample data
const int DATA[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const size_t LEN = 10;

class LinkedListIteratorTest : public ::testing::Test {
};

TEST_F(LinkedListIteratorTest, BeginAndDereference)
{
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);

    // Simple begin test
    LinkedList<int>::iterator i = a.begin();
    const LinkedList<int>::iterator j = a.begin();
    EXPECT_TRUE(i == j);
    EXPECT_FALSE(i != j);
    EXPECT_EQ(*i, *j);
}

TEST_F(LinkedListIteratorTest, IncrementDecrement)
{
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);

    LinkedList<int>::iterator i = a.begin();
    LinkedList<int>::iterator j = a.begin();
    i++;
    EXPECT_FALSE(i == j);
    i--;
    EXPECT_TRUE(i == j);
    ++i;
    EXPECT_FALSE(i == j);
    --i;
    EXPECT_TRUE(i == j);
}

TEST_F(LinkedListIteratorTest, End)
{
    LinkedList<int> a;
    for (uint32_t i = 0; i < LEN; ++i)
        a.add(DATA[i]);
    LinkedList<int>::iterator i = a.begin();
    uint32_t count = 0;
    for (; i != a.end(); ++i) {
        count++;
    }
    EXPECT_EQ(count, LEN);
}

TEST_F(LinkedListIteratorTest, Arrows)
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
    size_t index = 0;
    size_t lengths[9] = { 3, 5, 5, 3, 6, 4, 3, 4, 3 };
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        EXPECT_EQ(iter->length(), lengths[index++]);
    }
}
}