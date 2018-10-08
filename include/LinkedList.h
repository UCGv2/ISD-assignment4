// @author G. Hemingway, copyright 2018 - All rights reserved
//
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"
#include <cstdint>
#include <cstdlib>
#include <memory>

/**
 * Forward declarations.
 *
 * To understand why these are necessary, think about the compilation process
 * and how dependencies are instantiated. When a LinkedList<T> is instantiated,
 * a LinkedListIterator<T> and LinkedListConstIterator<T> must also be
 * instantiated, but they cannot be instantiated without a complete
 * LinkedList<T>, and so on it goes.
 *
 * To get around the mutual dependency issue, we use a trick called a "forward
 * declaration" - we simply declare that the class exists (without providing any
 * details about it!) and tell the compiler "we'll feed you the symbol
 * definitions later - just use this as a placeholder for now", and #include the
 * dependency once we're done, leaving it up to the compiler to fill in the
 * blanks.
 */

template <typename T> class LinkedListIterator;

template <typename T> class LinkedListConstIterator;

/**
 * An node-backed list implementation. This class attempts to provide certain
 * levels of exception safety (consult each method documentation for specifics)
 * and as such several assumptions are made:
 *
 * 1. The parameterizing type has a default constructor.
 * 2. The parameterizing type has a copy constructor.
 * 3. The parameterizing type has an assignment operator.
 * 4. The parameterizing type has a no-throw destructor.
 * 5. The parameterizing type has proper copy semantics.
 *
 * Note that you can make no other assumptions about the behavior of the
 * parameterizing type (including its behavior with respect to exceptions)
 * beyond those made here.
 *
 * To eliminate complex edge cases, this LinkedList is implemented as a doubly-
 * linked, circular chain of nodes that always contains a "dummy" node. With
 * this approach we never have to worry about checking for head and tail or
 * empty conditions. The node class is designed in such a way as to reduce the
 * amount of code in the actual list implementation.
 *
 * Implementation note 1: mTail should always point to the dummy node.
 * Implementation note 2: mTail->next should always point to the head node.
 *
 * Due to this node structure, most of the operations performed on the
 * LinkedList can execute safely without making backup copies of the list.
 *
 * This class provides a set of STL-style iterators. As with most
 * iterator implementations, modifying the LinkedList while iterating over it
 * invalidates all current iterators. Attempts to use invalidated iterators
 * constitutes undefined behavior.
 *
 */
template <typename T> class LinkedList {
public:
    // typedefs for interoperability/compatibility with STL containers
    // See C++17 standard §23.1 [container.requirements.general]
    typedef T value_type;
    typedef LinkedListIterator<T> iterator;
    typedef LinkedListConstIterator<T> const_iterator;

    /**
     * Initializes an empty LinkedList.
     * This operation provides strong exception safety.
     */
    LinkedList();

    /**
     * Initializes the LinkedList to be a copy of src.
     * This operation provides strong exception safety.
     *
     * @param src LinkedList to copy
     */
    LinkedList(const LinkedList<T>& src);

    /**
     * Makes this object a copy of rhs using the same guidelines as the copy
     * constructor. Note that calling this method on yourself (l = l;) is
     * equivalent to a no-op.
     * This operation provides strong exception safety.
     *
     * @param rhs LinkedList to copy
     * @return *this, used for chaining.
     */
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    /**
     * Destructor. Releases all resources held by this LinkedList.
     * This operation is no-throw under the assumption that the parameterizing
     * type's destructor is no-throw.
     */
    ~LinkedList() noexcept;

    /**
     * Adds value to the end of this LinkedList. The insertion is performed in
     * constant time.
     * This operation provides strong exception safety.
     *
     * @param value value to append to this LinkedList
     */
    void add(const T& value);

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
    void add(uint32_t index, const T& value);

    /**
     * Empties this LinkedList returning it to the same state as the default
     * constructor.
     * This operation is no-throw under the assumption that the parameterizing
     * type's destructor is no-throw.
     */
    void clear() noexcept;

    /**
     * Returns a constant reference to the element stored at the provided index.
     * If index is out of bounds, an std::out_of_range exception is thrown with
     * the index as its message.
     * This operation provides strong exception safety.
     *
     * @param index index of the element to return
     * @return constant reference to the element at the index.
     */
    const T& get(uint32_t index) const;

    /**
     * Returns a reference to the element stored at the provided index. If index
     * is out of bounds, an std::out_of_range exception is thrown with the index
     * as its message.
     * This operation provides strong exception safety.
     *
     * @param index index of the element to return
     * @return reference to the element at the index.
     */
    T& get(uint32_t index);

    /**
     * Returns true if and only if this LinkedList is logically equivalent to
     * rhs, i.e. the size and contents are equal.
     * This operation provides strong exception safety.
     *
     * @param rhs the LinkedList being compared to
     * @return true iff logically equivalent
     */
    bool operator==(const LinkedList<T>& rhs) const;

    /**
     * Returns false if this LinkedList is equal to rhs and true otherwise.
     * This operation provides strong exception safety.
     *
     * @param rhs the LinkedList being compared to
     * @return true iff not logically equivalent
     */
    bool operator!=(const LinkedList<T>& rhs) const;

    /**
     * Returns a constant iterator to the beginning.
     * This operation is a no-throw.
     *
     * @return
     */
    const_iterator begin() const noexcept;

    /**
     * Returns an iterator to the beginning.
     * This operation is a no-throw.
     *
     * @return
     */
    iterator begin() noexcept;

    /**
     * Returns a constant iterator to the end.
     * This operation is a no-throw.
     *
     * @return
     */
    const_iterator end() const noexcept;

    /**
     * Returns an iterator to the end.
     * This operation is a no-throw.
     *
     * @return
     */
    iterator end() noexcept;

    /**
     * Returns true if this LinkedList is empty and false otherwise.
     * This operation is a no-throw.
     *
     * @return
     */
    bool isEmpty() const noexcept;

    /**
     * Removes the element at the specified index. If index is out of bounds
     * an std::out_of_range exception is thrown with index as its messaged. If
     * index points to the first or last element, this operation is performed in
     * constant time. Otherwise, time proportional to index is needed.
     * This operation provides strong exception safety.
     *
     * @param index index of the object to remove.
     */
    void remove(uint32_t index);

    /**
     * Sets the element at the specified index to the provided value. If index
     * is out of bounds, an std::out_of_range exception is thrown with the index
     * as its message. This method completes in time proportional to index.
     * This operation provides strong exception safety.
     *
     * @param index index of the object to set
     * @param value the new value
     */
    void set(uint32_t index, const T& value);

    /**
     * Return the size of this LinkedList.
     * This operation is a no-throw.
     *
     * @return
     */
    uint32_t size() const noexcept;

private:
    /**
     * Given an index, this method throws an std::out_of_range with the index as
     * its message if index is out of bounds or is a no-op otherwise.
     * This operation provides strong exception safety.
     *
     * @param index index to check
     */
    void rangeCheck(uint32_t index) const;

    /**
     * Removes from this LinkedList the node pointed to by iter.
     * This operation is no-throw under the assumption that the parameterizing
     * type's destructor is no-throw.
     *
     * @pre the iterator iter must point to an element (or end) within this list
     * @param iter iterator pointing to the node that should be removed.
     */
    void removeNode(iterator iter) noexcept;

    /**
     * Swaps the contents of this LinkedList with that of other in constant time.
     * This operation is a no-throw.
     *
     * @param other the LinkedList to swap with
     */
    void swap(LinkedList<T>& rhs) noexcept;

    /**
     * The logical size of the list. This does not include the dummy node
     */
    uint32_t mSize;

    /**
     * (unique) pointer to the dummy node. mTail->mNext points to the first valid
     * element of this list (if one exists). The use of std::unique_ptr
     * facilitates implementing strong exception safety (RAII).
     */
    std::unique_ptr<LinkedListNode<T>> mTail;
};

#include "../src/LinkedList.cpp"
#include "LinkedListConstIter.h"
#include "LinkedListIter.h"

#endif // LINKED_LIST_H
