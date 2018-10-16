#include "LinkedListConstIter.h"

template <typename T>
bool LinkedListConstIterator<T>::operator==(const LinkedListConstIterator<T>& rhs) const noexcept
{
    return mPtr == rhs.mPtr;
}

template <typename T>
bool LinkedListConstIterator<T>::operator!=(const LinkedListConstIterator<T>& rhs) const noexcept
{
    return mPtr != rhs.mPtr;
}

template <typename T> const T& LinkedListConstIterator<T>::operator*() const
{
    return mPtr->mItem;
}

template <typename T> const T* LinkedListConstIterator<T>::operator->() const
{
    T* itemPtr = &mPtr->mItem;
    return itemPtr;
}

template <typename T> LinkedListConstIterator<T>& LinkedListConstIterator<T>::operator++()
{
    mPtr = mPtr->mNext;
    return *this;
}

template <typename T> const LinkedListConstIterator<T> LinkedListConstIterator<T>::operator++(int)
{
    LinkedListConstIterator<T> retPtr = *this;
    mPtr = mPtr->mNext;
    return retPtr;
}

template <typename T> LinkedListConstIterator<T>& LinkedListConstIterator<T>::operator--()
{
    mPtr = mPtr->mPrev;
    return *this;
}

template <typename T> const LinkedListConstIterator<T> LinkedListConstIterator<T>::operator--(int)
{
    LinkedListConstIterator<T> retPtr = *this;
    mPtr = mPtr->mPrev;
    return retPtr;
}

template <typename T>
LinkedListConstIterator<T>::LinkedListConstIterator(LinkedListNode<T>* ptr)
    : mPtr(ptr)
{
}
