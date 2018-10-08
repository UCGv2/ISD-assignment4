// @author G. Hemingway, copyright 2018 - All rights reserved
//
#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

// Forward declarations (see include/LinkedList.h for an explanation)
template <typename T> class LinkedList;
template <typename T> class LinkedListIterator;
template <typename T> class LinkedListConstIterator;

/**
 * A helper utility class for implementing the LinkedList. Most of this class is
 * private so that only its friends may use its functionality.
 */
template <typename T> class LinkedListNode {
public:
    /**
     * Initializes this node to store the provided item. The next and previous
     * pointers of this node are set to point to the node itself.
     * This operation provides strong exception safety.
     *
     * @param item the item to set
     */
    explicit LinkedListNode(const T& item = T());

    /**
     * Destructor. Unlinks this node from its neighbors.
     * This operation is a no-throw.
     */
    ~LinkedListNode() noexcept;

private:
    friend class LinkedList<T>;
    friend class LinkedListIterator<T>;
    friend class LinkedListConstIterator<T>;

    /**
     * Initializes this node with the provided values, i.e. the node stores
     * item, follows prev and precedes next in the linked list. Modifies prev
     * and next to maintain the linked list invariant.  Prev and next should
     * never be nullptr, so don't bother checking for that.
     * This operation provides strong exception safety.
     *
     * @param item item to store in the node
     * @param prev pointer to the previous node
     * @param next pointer to the next node
     */
    LinkedListNode(const T& item, LinkedListNode<T>* prev, LinkedListNode<T>* next);

    /**
     * Establishes the proper linkage between the provided nodes.  First and
     * second should never be nullptr, so don't bother checking for that.
     *
     * @param   first node to link as preceding node
     * @param   second node to link as succeeding node
     * @post    first and second are linked in that order
     */
    static void link(LinkedListNode<T>* first, LinkedListNode<T>* second) noexcept;

    T mItem;
    LinkedListNode<T>* mPrev;
    LinkedListNode<T>* mNext;
};

#include "../src/LinkedListNode.cpp"

#endif // LINKED_LIST_NODE_H
