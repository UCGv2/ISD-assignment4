// @author G. Hemingway, copyright 2018 - All rights reserved
//
#ifndef LINKEDLISTCONSTITER_H
#define LINKEDLISTCONSTITER_H

#include <exception>
#include <iterator>

template <typename T> class LinkedList;
template <typename T> class LinkedListNode;

/**
 * This header contains the const iterator for the
 * LinkedList container.  All of the methods for the classes should be self-explanatory
 *
 */
template <typename T>
class LinkedListConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    LinkedListConstIterator() = delete;

    bool operator==(const LinkedListConstIterator<T>& rhs) const noexcept;
    bool operator!=(const LinkedListConstIterator<T>& rhs) const noexcept;
    const T& operator*() const;
    const T* operator->() const;
    LinkedListConstIterator<T>& operator++();
    const LinkedListConstIterator<T> operator++(int);
    LinkedListConstIterator<T>& operator--();
    const LinkedListConstIterator<T> operator--(int);

private:
    friend class LinkedList<T>;
    LinkedListNode<T>* mPtr;
    explicit LinkedListConstIterator(LinkedListNode<T>* ptr);
};

#include "../src/LinkedListConstIter.cpp"

#endif // LINKEDLISTCONSTITER_H
