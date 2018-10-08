// @author G. Hemingway, copyright 2018 - All rights reserved
//
#ifndef LINKEDLISTITER_H
#define LINKEDLISTITER_H

#include <exception>
#include <iterator>

template <typename T> class LinkedList;
template <typename T> class LinkedListNode;

/**
 * This header contains both the normal iterator and the const iterator for the
 * LinkedList container.  All of the methods for both classes should be self-explanatory
 *
 */
template <typename T>
class LinkedListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    LinkedListIterator() = delete;

    bool operator==(const LinkedListIterator<T>& rhs) const noexcept;
    bool operator!=(const LinkedListIterator<T>& rhs) const noexcept;
    T& operator*() const;
    T* operator->() const;
    LinkedListIterator<T>& operator++();
    const LinkedListIterator<T> operator++(int);
    LinkedListIterator<T>& operator--();
    const LinkedListIterator<T> operator--(int);

private:
    friend class LinkedList<T>;
    LinkedListNode<T>* mPtr;
    explicit LinkedListIterator(LinkedListNode<T>* ptr);
};

#include "../src/LinkedListIter.cpp"

#endif // LINKEDLISTITER_H
