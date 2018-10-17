/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: LinkedList.cpp
 */

#include "LinkedList.h"
#include <LinkedListConstIter.h>
#include <LinkedListIter.h>

/**
 * Initializes an empty LinkedList.
 * This operation provides strong exception safety.
 */
template <typename T>
LinkedList<T>::LinkedList()
    : mSize(0)
    , mTail(new LinkedListNode<T>)
{
}

/**
 * Initializes the LinkedList to be a copy of src.
 * This operation provides strong exception safety.
 *
 * @param src LinkedList to copy
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src)
    : mSize(src.mSize)
    , mTail(new LinkedListNode<T>)
{
    try {
        for (LinkedListConstIterator<T> a = src.begin(); a != src.end(); ++a) {
            if (a == src.begin()) {
                new LinkedListNode<T>(a.mPtr->mItem, mTail->mNext, mTail->mPrev);
            } else {
                LinkedListNode<T>* endPtr = &*mTail;
                new LinkedListNode<T>(a.mPtr->mItem, mTail->mPrev, endPtr);
            }
        }
    } catch (const std::exception& except) {
        mTail.reset();
        throw except;
    }
}
/**
 * Makes this object a copy of rhs using the same guidelines as the copy
 * constructor. Note that calling this method on yourself (l = l;) is
 * equivalent to a no-op.
 * This operation provides strong exception safety.
 *
 * @param rhs LinkedList to copy
 * @return *this, used for chaining.
 */
template <typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if (*this != rhs) {
        LinkedList<T> copy(rhs);
        swap(copy);
    }
    return *this;
}

/**
 * Destructor. Releases all resources held by this LinkedList.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 */
template <typename T> LinkedList<T>::~LinkedList() noexcept
{
    clear();
    mTail.reset();
}

/**
 * Adds value to the end of this LinkedList. The insertion is performed in
 * constant time.
 * This operation provides strong exception safety.
 *
 * @param value value to append to this LinkedList
 */
template <typename T> void LinkedList<T>::add(const T& value)
{
    LinkedList<T> copy(*this);
    if (copy.mSize == 0) {
        new LinkedListNode<T>(value, copy.mTail->mNext, copy.mTail->mPrev);
    } else {
        LinkedListNode<T>* endPtr = &*copy.mTail;
        new LinkedListNode<T>(value, copy.mTail->mPrev, endPtr);
    }
    ++copy.mSize;
    swap(copy);
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
    LinkedList<T> copy(*this);
    uint32_t updtSize = copy.mSize;
    uint32_t indexBuddy = 0;
    LinkedListIterator<T> adder(nullptr);
    bool indexMet = false;
    LinkedListNode<T>* endPtr = &*copy.mTail;
    if (updtSize == 0 && updtSize != index) {
        new LinkedListNode<T>(T(), copy.mTail->mNext, copy.mTail->mPrev);
        ++updtSize;
    } else if (updtSize == 0 && updtSize == index) {
        new LinkedListNode<T>(value, copy.mTail->mNext, copy.mTail->mPrev);
        ++updtSize;
        indexMet = true;
    } else if (updtSize - 1 == index) {
        new LinkedListNode<T>(value, copy.mTail->mPrev, endPtr);
        indexMet = true;
    }
    for (LinkedListIterator<T> a = copy.begin(); a != copy.end() && !indexMet; ++a) {
        adder = a;
        if (index >= updtSize) {
            ++updtSize;
            if (updtSize - 1 < index) {
                new LinkedListNode<T>(T(), copy.mTail->mPrev, endPtr);
            } else if (updtSize - 1 == index) {
                new LinkedListNode<T>(value, copy.mTail->mPrev, endPtr);
                indexMet = true;
            }
        } else if (indexBuddy == index) {
            new LinkedListNode<T>(value, adder.mPtr->mPrev, adder.mPtr);
            ++updtSize;
            indexMet = true;
        }
        ++indexBuddy;
    }
    copy.mSize = updtSize;

    swap(copy);
}

/**
 * Empties this LinkedList returning it to the same state as the default
 * constructor.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 */
template <typename T> void LinkedList<T>::clear() noexcept
{
    while (mTail->mNext != &*mTail) {
        LinkedListNode<T>* begone = mTail->mNext;
        delete begone;
    }
    mSize = 0;
}

/**
 * Returns a constant reference to the element stored at the provided index.
 * If index is out of bounds, an std::out_of_range exception is thrown with
 * the index as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return constant reference to the element at the index.
 */
template <typename T> const T& LinkedList<T>::get(uint32_t index) const
{
    rangeCheck(index);
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

/**
 * Returns a reference to the element stored at the provided index. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return reference to the element at the index.
 */
template <typename T> T& LinkedList<T>::get(uint32_t index)
{
    return const_cast<T&>(static_cast<const LinkedList<T>*>(this)->get(index));
}

/**
 * Returns true if and only if this LinkedList is logically equivalent to
 * rhs, i.e. the size and contents are equal.
 * This operation provides strong exception safety.
 *
 * @param rhs the LinkedList being compared to
 * @return true iff logically equivalent
 */
template <typename T> bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
    return mSize == rhs.mSize;
}

/**
 * Returns false if this LinkedList is equal to rhs and true otherwise.
 * This operation provides strong exception safety.
 *
 * @param rhs the LinkedList being compared to
 * @return true iff not logically equivalent
 */
template <typename T> bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const
{
    return mSize != rhs.mSize;
}

/**
 * Returns a constant iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> LinkedListConstIterator<T> LinkedList<T>::begin() const noexcept
{
    LinkedListConstIterator<T> beg(mTail->mNext);
    return beg;
}

/**
 * Returns an iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> LinkedListIterator<T> LinkedList<T>::begin() noexcept
{
    LinkedListIterator<T> beg(mTail->mNext);
    return beg;
}

/**
 * Returns a constant iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> LinkedListConstIterator<T> LinkedList<T>::end() const noexcept
{
    LinkedListNode<T>* endPtr = &*mTail;
    LinkedListConstIterator<T> end(endPtr);
    return end;
}

/**
 * Returns an iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> LinkedListIterator<T> LinkedList<T>::end() noexcept
{
    LinkedListNode<T>* endPtr = &*mTail;
    LinkedListIterator<T> end(endPtr);
    return end;
}

/**
 * Returns true if this LinkedList is empty and false otherwise.
 * This operation is a no-throw.
 *
 * @return
 */
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
    LinkedList<T> copy(*this);
    rangeCheck(index);
    uint32_t shrinkSize = copy.mSize;
    LinkedListIterator<T> subtractor(nullptr);
    uint32_t count = 0;
    for (LinkedListIterator<T> a = copy.begin(); a != copy.end() && count <= index; ++a) {
        subtractor = a;
        if (count == index) {
            removeNode(subtractor);
            --shrinkSize;
        }
        ++count;
    }

    copy.mSize = shrinkSize;
    swap(copy);
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

    LinkedList<T> copy(*this);
    rangeCheck(index);
    uint32_t count = 0;
    for (LinkedListIterator<T> a = copy.begin(); a != copy.end(); ++a) {
        if (index == count) {
            a.mPtr->mItem = value;
        }
        ++count;
    }
    swap(copy);
}
/**
 * Return the size of this LinkedList.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> uint32_t LinkedList<T>::size() const noexcept
{
    return mSize;
}

/**
 * Given an index, this method throws an std::out_of_range with the index as
 * its message if index is out of bounds or is a no-op otherwise.
 * This operation provides strong exception safety.
 *
 * @param index index to check
 */
template <typename T> void LinkedList<T>::rangeCheck(uint32_t index) const
{
    if (mSize == 0 || index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
}

/**
 * Removes from this LinkedList the node pointed to by iter.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 *
 * @pre the iterator iter must point to an element (or end) within this list
 * @param iter iterator pointing to the node that should be removed.
 */
template <typename T> void LinkedList<T>::removeNode(iterator iter) noexcept
{
    LinkedListNode<T>* begone = iter.mPtr;
    delete begone;
}

/**
 * Swaps the contents of this LinkedList with that of other in constant time.
 * This operation is a no-throw.
 *
 * @param other the LinkedList to swap with
 */
template <typename T> void LinkedList<T>::swap(LinkedList<T>& rhs) noexcept
{
    LinkedList<T> copy(rhs);
    std::swap(mSize, copy.mSize);
    mTail.swap(copy.mTail);
}