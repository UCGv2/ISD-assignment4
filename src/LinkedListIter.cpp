#include "LinkedListIter.h"

template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr == rhs.mPtr;
}

template <typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr != rhs.mPtr;
}

template <typename T> T& LinkedListIterator<T>::operator*() const
{
    return mPtr->mItem;
}

template <typename T> T* LinkedListIterator<T>::operator->() const
{
    T* itemPtr = &mPtr->mItem;
    return itemPtr;
}

template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator++()
{
    mPtr = mPtr->mNext;
    return *this;
}

template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator++(int)
{
    LinkedListIterator<T> retPtr = *this;
    mPtr = mPtr->mNext;
    return retPtr;
}

template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator--()
{
    mPtr = mPtr->mPrev;
    return *this;
}

template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator--(int)
{
    LinkedListIterator<T> retPtr = *this;
    mPtr = mPtr->mPrev;
    return retPtr;
}

template <typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedListNode<T>* ptr)
    : mPtr(ptr)
{
}
