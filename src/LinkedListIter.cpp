/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: LinkedListIter.cpp
 */
#include "LinkedListIter.h"

/**
 * Equivalence operator checks whether two iterators have mPtr that
 * point to the same thing
 * @tparam T data Type
 * @param rhs The other Iterator
 * @return the equality of the two pointers
 */
template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr == rhs.mPtr;
}

/**
 * NonEquivalence operator checks whether two iterators have mPtr that do not
 * point to the same thing
 * @tparam T data Type
 * @param rhs The other Iterator
 * @return the inequality of the two pointers
 */
template <typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr != rhs.mPtr;
}
/**
 * Dereference operator.
 * @return A T & to the value pointed to by mPtr.
 */
template <typename T> T& LinkedListIterator<T>::operator*() const
{
    return mPtr->mItem;
}

/**
 * Dereference operator.
 * @return A pointer to the value pointed to by mPtr.
 */
template <typename T> T* LinkedListIterator<T>::operator->() const
{
    T* itemPtr = &mPtr->mItem;
    return itemPtr;
}
/**
 * Preincrement operator.
 * @return *this after the increment.
 */
template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator++()
{
    mPtr = mPtr->mNext;
    return *this;
}
/**
 * Postincrement operator.
 * @return The iterator before the increment.
 */
template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator++(int)
{
    LinkedListIterator<T> retPtr = *this;
    mPtr = mPtr->mNext;
    return retPtr;
}

/**
 * Predecrement operator.
 * @return *this after the decrement.
 */
template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator--()
{
    mPtr = mPtr->mPrev;
    return *this;
}
/**
 * Postdecrement operator.
 * @return The iterator before the decrement.
 */
template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator--(int)
{
    LinkedListIterator<T> retPtr = *this;
    mPtr = mPtr->mPrev;
    return retPtr;
}

/**
 * Ctor for LinkedListIterator
 * @param ptr the linkedListNode pointer to be used as mPtr
 */
template <typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedListNode<T>* ptr)
    : mPtr(ptr)
{
}
