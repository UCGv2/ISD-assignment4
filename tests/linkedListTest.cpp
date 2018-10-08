// @author G. Hemingway, copyright 2018 - All rights reserved
//
#include "LinkedList.h"
#include "AllocationTracker.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <vector>

// Outputs the contents of the LinkedList to the ostream using iterators.
template <typename T> std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    std::copy(list.begin(), list.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

// Outputs the contents of the LinkedList to the ostream using get
template <typename T> std::ostream& writeListViaGet(std::ostream& os, const LinkedList<T>& list)
{
    for (size_t i = 0; i < list.size(); ++i) {
        os << list.get(i);
        if (i != list.size() - 1)
            os << " ";
    }
    return os;
}

namespace {

// Sample data
const int DATA[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const size_t LEN = 10;

// The fixture for testing LinkedList and LinkedListIterator.
class LinkedListTest : public ::testing::Test {
};

TEST_F(LinkedListTest, Constructor)
{
    {
        // 1 alloc in default
        LinkedList<AllocationTracker> list;
        // Default ctor failed to create dummy node
        EXPECT_EQ(AllocationTracker::getCount(), 1UL);
    }
    // Sanity check
    EXPECT_EQ(AllocationTracker::getCount(), 0UL);
    {
        LinkedList<AllocationTracker> list;
        LinkedList<AllocationTracker> copy(list);
        // dummy has to be created for both
        EXPECT_EQ(AllocationTracker::getCount(), 2UL);
        // Try a different constructor
        LinkedList<AllocationTracker> assignment;
        // Assignment operator
        assignment = copy;
        EXPECT_EQ(AllocationTracker::getCount(), 3UL);
    }
    // Sanity check
    EXPECT_EQ(AllocationTracker::getCount(), 0UL);

    LinkedList<int> a, c, d;
    EXPECT_TRUE(a.isEmpty());
    EXPECT_EQ(a.size(), 0UL);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);
    a.add(5);
    LinkedList<int> b(a);
    EXPECT_EQ(b.size(), 5UL);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(b.get(i), i + 1);
    }
    d = c = b = a;
    EXPECT_EQ(b.size(), 5UL);
    EXPECT_EQ(c.size(), 5UL);
    EXPECT_EQ(d.size(), 5UL);
}

TEST_F(LinkedListTest, ConstructorAssignmentAndAccess)
{
    const LinkedList<int> list1;
    // check size() after default constructor
    EXPECT_EQ(list1.size(), 0UL);

    // check isEmpty() after default construction
    EXPECT_TRUE(list1.isEmpty());

    const LinkedList<int> list2(list1);
    // check size() after copy constructor
    EXPECT_EQ(list2.size(), 0UL);

    LinkedList<int> list3;
    list3 = list2;
    // check size after assignment operator
    EXPECT_EQ(list3.size(), 0UL);

    std::ostringstream os1, os2, os3;

    writeListViaGet(os1, list1);
    writeListViaGet(os2, list2);
    writeListViaGet(os3, list3);

    const std::string correct = "";
    // constructor list
    EXPECT_EQ(os1.str(), correct);
    // copy constructor did not copy values
    EXPECT_EQ(os2.str(), correct);
    // assignment operator did not copy values
    EXPECT_EQ(os3.str(), correct);

    // expect std::out_of_range exception
    EXPECT_THROW(list1.get(1), std::out_of_range);
}

TEST_F(LinkedListTest, StrenuousCopyAndAssignmentAndIterator)
{
    EXPECT_EQ(AllocationTracker::getCount(), 0UL);
    {
        std::vector<std::string> sentence;
        sentence.push_back("the");
        sentence.push_back("quick");
        sentence.push_back("brown");
        sentence.push_back("fox");
        sentence.push_back("jumped");
        sentence.push_back("over");
        sentence.push_back("the");
        sentence.push_back("lazy");
        sentence.push_back("dog");

        LinkedList<std::string> linked_sentence;
        for (const std::string& s : sentence)
            linked_sentence.add(s);

        LinkedList<std::string> linked_sentence_copy(linked_sentence);

        EXPECT_TRUE(std::equal(sentence.begin(), sentence.end(), linked_sentence.begin()));
        EXPECT_TRUE(std::equal(linked_sentence.begin(), linked_sentence.end(), sentence.begin()));
        EXPECT_TRUE(std::equal(sentence.begin(), sentence.end(), linked_sentence_copy.begin()));
        EXPECT_TRUE(
            std::equal(linked_sentence_copy.begin(), linked_sentence_copy.end(), sentence.begin()));

        EXPECT_EQ(sentence.size(), linked_sentence.size());
        EXPECT_EQ(linked_sentence.size(), linked_sentence_copy.size());

        linked_sentence_copy.clear();
        EXPECT_EQ(linked_sentence_copy.size(), 0UL);
        EXPECT_FALSE(std::equal(sentence.begin(), sentence.end(), linked_sentence_copy.begin()));

        linked_sentence_copy = linked_sentence;
        EXPECT_TRUE(std::equal(sentence.begin(), sentence.end(), linked_sentence_copy.begin()));
        EXPECT_TRUE(
            std::equal(linked_sentence_copy.begin(), linked_sentence_copy.end(), sentence.begin()));
    }
}

TEST_F(LinkedListTest, Add)
{
    {
        LinkedList<AllocationTracker> list;
        for (uint32_t i = 0; i < 10; ++i) {
            list.add(AllocationTracker());
            EXPECT_EQ(list.size(), i + 1);
            EXPECT_EQ(AllocationTracker::getCount(), i + 2);
        }
    }
    {
        LinkedList<int> list;
        for (uint32_t i = 0; i < 10; ++i)
            list.add(i + 1);
        EXPECT_EQ(list.size(), 10U);

        std::ostringstream os;
        writeListViaGet(os, list);

        std::string correct = "1 2 3 4 5 6 7 8 9 10";
        EXPECT_EQ(os.str(), correct);
    }
    {
        LinkedList<int> list;
        for (uint32_t i = 0; i < 10; ++i)
            list.add(2 * i, (int)(i + 1));
        EXPECT_EQ(list.size(), 19U);

        std::ostringstream os;
        writeListViaGet(os, list);

        std::string correct = "1 0 2 0 3 0 4 0 5 0 6 0 7 0 8 0 9 0 10";
        EXPECT_EQ(os.str(), correct);
    }
    {
        LinkedList<std::string> list;
        list.add(90, "qwerty");

        for (uint32_t i = 0; i < 90; ++i)
            EXPECT_EQ(list.get(i), "");
        EXPECT_EQ(list.size(), 91U);

        EXPECT_THROW(list.get(91), std::out_of_range);

        for (uint32_t i = 90; i < 100; ++i) {
            EXPECT_EQ(list.get(i), "qwerty");
            list.add(10, "foo");
        }
        EXPECT_EQ(list.size(), 101U);

        EXPECT_EQ(list.get(100), "qwerty");

        for (uint32_t i = 10; i < 20; ++i)
            EXPECT_EQ(list.get(i), "foo");

        EXPECT_THROW(list.get(101), std::out_of_range);
    }
}

TEST_F(LinkedListTest, Modifiers)
{
    LinkedList<int> list;
    for (uint32_t i = 0; i < 10; ++i) {
        EXPECT_EQ(list.size(), i);
        list.add(0);
        list.get(i) = (uint32_t)i;
    }

    std::ostringstream os;
    writeListViaGet(os, list);
    std::string correct = "0 1 2 3 4 5 6 7 8 9";
    EXPECT_EQ(os.str(), correct);

    // expect std::out_of_range exception
    EXPECT_THROW(list.get(10) = 42, std::out_of_range);
    // we want (exception.what() == std::string("10"))

    for (uint32_t i = 0; i < list.size(); ++i) {
        list.set(i, 2 * (int)i);
    }
    std::ostringstream os2;
    writeListViaGet(os2, list);
    correct = "0 2 4 6 8 10 12 14 16 18";
    EXPECT_EQ(os2.str(), correct);
}

TEST_F(LinkedListTest, Equality)
{
    LinkedList<int> list1;
    LinkedList<int> list2;

    for (size_t i = 0; i < 10; ++i) {
        list1.add(0);
        list2.add(0);
    }
    list2.add(0);

    // Make sure op== accounts for size
    EXPECT_FALSE(list1 == list2);
    EXPECT_TRUE(list1 != list2);

    LinkedList<uint32_t> list3;
    list3.add(1);
    list3.add(3);
    list3.add(4);
    list3.add(7);
    list3.add(99);

    LinkedList<uint32_t> list4;
    list4.add(1);
    list4.add(3);
    list4.add(4);
    list4.add(7);
    list4.add(99);

    EXPECT_TRUE(list3 == list4);
    EXPECT_FALSE(list3 != list4);

    list3.remove(2);
    EXPECT_FALSE(list3 == list4);
    EXPECT_TRUE(list3 != list4);
}

TEST_F(LinkedListTest, Clear)
{
    LinkedList<AllocationTracker> list;
    list.clear();
    // clear() must release resources - but not the dummy node
    EXPECT_EQ(AllocationTracker::getCount(), 1UL);

    for (size_t i = 0; i < 10; ++i)
        list.add(AllocationTracker());

    // clear() must release resources - but not the dummy node
    list.clear();
    EXPECT_EQ(AllocationTracker::getCount(), 1UL);
}

TEST_F(LinkedListTest, Remove)
{
    {
        LinkedList<AllocationTracker> list;
        for (uint32_t i = 0; i < 10; ++i)
            list.add(AllocationTracker());

        for (uint32_t i = 10; i > 0; --i) {
            list.remove(i - 1);
            EXPECT_EQ(list.size(), (uint32_t)(i - 1));
            EXPECT_EQ(AllocationTracker::getCount(), list.size() + 1);
        }
    }
    {
        LinkedList<int> list;
        // expect std::out_of_range
        EXPECT_THROW(list.remove(0), std::out_of_range);
        // (exception.what() == std::string("0"))
    }
}

TEST_F(LinkedListTest, Iterators)
{
    LinkedList<int> list;
    for (uint32_t i = 0; i < LEN; ++i)
        list.add(0);

    std::string correct = "0 0 0 0 0 0 0 0 0 0 ";
    std::ostringstream os1;

    // check for const_iterator error
    os1 << list;
    EXPECT_EQ(os1.str(), correct);

    std::copy(DATA, DATA + LEN, list.begin());
    correct = "0 1 2 3 4 5 6 7 8 9 ";

    std::ostringstream os2;
    os2 << list;
    // check for iterator error
    EXPECT_EQ(os2.str(), correct);
}
}
