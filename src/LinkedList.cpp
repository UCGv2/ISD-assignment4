//
// Created by fours on 10/12/2018.
//

#include "LinkedList.h"
#include <LinkedListIter.h>

template <typename T>
LinkedList<T>::LinkedList()
    : mSize(0)
    , mTail(new LinkedListNode<T>)
{
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src)
    : mTail(new LinkedListNode<T>)
{
    if (*this != src) {
        for (LinkedListConstIterator<T> a = src.begin(); a != src.end(); ++a) {
            add(a.operator*());
        }
        mSize = src.mSize;
    }
}

template <typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if (*this != rhs) {
        LinkedList<T> copy(rhs);
        std::swap(mSize, copy.mSize);
        swap(copy);
    }
    return *this;
}

template <typename T> LinkedList<T>::~LinkedList() noexcept
{
    clear();
    mTail.reset();
}

template <typename T> bool LinkedList<T>::isEmpty() const noexcept
{
    return mSize == 0;
}
/**
 * Removes the element at the specified index. If index is out of bounds
 * an std::out_of_range exception is thrown with index as its messaged. If
 * index points to the first or last element, this operation is performed in
 * constant time. Otherwise, time proportional to index is needed.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to remove.
 */
template <typename T> void LinkedList<T>::remove(uint32_t index)
{
    uint32_t shrinkSize = mSize;
    LinkedListIterator<T> subtractor(nullptr);
    if (mSize == 0 || index > mSize - 1) {
        throw std::out_of_range(std::to_string(index));
    } else {
        uint32_t count = 0;
        for (LinkedListIterator<T> a = begin(); a != end(); ++a) {
            subtractor = a;
            if (count == index) {
                LinkedListNode<T>* begone = subtractor.mPtr;
                delete begone;
                --shrinkSize;
            }
            ++count;
        }
    }
    mSize = shrinkSize;
}

template <typename T> uint32_t LinkedList<T>::size() const noexcept
{
    return mSize;
}

template <typename T> void LinkedList<T>::add(const T& value)
{
    if (mSize == 0) {
        new LinkedListNode<T>(value, mTail->mNext, mTail->mPrev);
    } else {
        LinkedListNode<T>* endPtr = &*mTail;
        new LinkedListNode<T>(value, mTail->mPrev, endPtr);
    }
    ++mSize;
}
/**
 * Inserts value at the specified index. All elements at or to the right of
 * index are shifted down by one spot. Time proportional to the maximum of
 * the size of this LinkedList or index is needed to perform this operation.
 * In particular, note that this operation does not perform the tail
 * insertion optimization that add(const T& value) offers. If this
 * LinkedList needs to be enlarged (index is out of range) default values
 * are used to fill the gaps.
 * This operation provides strong exception safety.
 *
 * @param index index at which to insert value
 * @param value the element to insert
 */
template <typename T> void LinkedList<T>::add(uint32_t index, const T& value)
{
    // wake up and fix this
    uint32_t updtSize = mSize;
    uint32_t indexBuddy = 0;
    LinkedListIterator<T> adder(nullptr);
    bool indexMet = false;
    if (updtSize == 0 && updtSize != index) {
        new LinkedListNode<T>(T(), mTail->mNext, mTail->mPrev);
        ++updtSize;
    } else if (updtSize == 0 && updtSize == index) {
        new LinkedListNode<T>(value, mTail->mNext, mTail->mPrev);
        ++updtSize;
        indexMet = true;
    }
    for (LinkedListIterator<T> a = begin(); a != end(); ++a) {
        adder = a;
        if (index >= updtSize) {
            ++updtSize;
            LinkedListNode<T>* endPtr = &*mTail;
            if (updtSize - 1 < index) {
                new LinkedListNode<T>(T(), mTail->mPrev, endPtr);
            } else if (updtSize - 1 == index) {
                new LinkedListNode<T>(value, mTail->mPrev, endPtr);
                indexMet = true;
            }
        } else if (!indexMet && indexBuddy == index) {
            new LinkedListNode<T>(value, adder.mPtr->mPrev, adder.mPtr);
            ++updtSize;
        }
        ++indexBuddy;
    }
    mSize = updtSize;
}
template <typename T> void LinkedList<T>::clear() noexcept
{
    while (mTail->mNext != &*mTail) {
        LinkedListNode<T>* begone = mTail->mNext;
        mTail->mNext = mTail->mNext->mNext;
        delete begone;
    }

    mSize = 0;
}
template <typename T> const T& LinkedList<T>::get(uint32_t index) const
{
    if (mSize == 0 || index > mSize - 1) {
        throw std::out_of_range(std::to_string(index));
    }
    LinkedListConstIterator<T> ret = begin();
    uint32_t count = 0;
    for (LinkedListConstIterator<T> a = begin(); a != end() && count <= index; ++a) {
        if (count == index) {
            ret = a;
        }
        ++count;
    }
    return *ret;
}
template <typename T> T& LinkedList<T>::get(uint32_t index)
{
    if (mSize == 0 || index > mSize - 1) {
        throw std::out_of_range(std::to_string(index));
    } else {
        LinkedListIterator<T> ret = begin();
        uint32_t count = 0;
        for (LinkedListIterator<T> a = begin(); a != end() && count <= index; ++a) {
            if (count == index) {
                ret = a;
            }
            ++count;
        }
        return *ret;
    }
}
template <typename T> bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
    return mSize == rhs.mSize;
}
template <typename T> bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const
{
    return mSize != rhs.mSize;
}
template <typename T> LinkedListIterator<T> LinkedList<T>::begin() noexcept
{
    LinkedListIterator<T> beg(mTail->mNext);
    return beg;
}

template <typename T> LinkedListConstIterator<T> LinkedList<T>::begin() const noexcept
{
    LinkedListConstIterator<T> beg(mTail->mNext);
    return beg;
}
template <typename T> LinkedListIterator<T> LinkedList<T>::end() noexcept
{
    LinkedListNode<T>* endPtr = &*mTail;
    LinkedListIterator<T> end(endPtr);
    return end;
}

template <typename T> LinkedListConstIterator<T> LinkedList<T>::end() const noexcept
{
    LinkedListNode<T>* endPtr = &*mTail;
    LinkedListConstIterator<T> end(endPtr);
    return end;
}

/**
 * Sets the element at the specified index to the provided value. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message. This method completes in time proportional to index.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to set
 * @param value the new value
 */
template <typename T> void LinkedList<T>::set(uint32_t index, const T& value)
{
    if (mSize == 0 || index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    } else {
        uint32_t count = 0;
        for (LinkedListIterator<T> a = begin(); a != end(); ++a) {
            if (index == count) {
                a.mPtr->mItem = value;
            }
            ++count;
        }
    }
}
template <typename T> void LinkedList<T>::rangeCheck(uint32_t index) const
{
    if (mSize == 0 || index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
}
template <typename T> void LinkedList<T>::removeNode(iterator iter) noexcept
{
    LinkedListNode<T>* begone = iter.mPtr;
    delete begone;
}
template <typename T> void LinkedList<T>::swap(LinkedList<T>& rhs) noexcept
{
    mTail.swap(rhs.mTail);
}