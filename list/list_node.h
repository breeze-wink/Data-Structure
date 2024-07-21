#pragma once

namespace DataStructure::list
{
    template <typename T>
    class ListNode
    {
        typedef ListNode<T> Node;
    public:
        ListNode() = delete;
        ListNode(const T & value) : m_value(value), m_prev(nullptr), m_next(nullptr) {}
        ~ListNode() {}

    public:
        T m_value;
        Node * m_prev;
        Node * m_next;
    };
}
