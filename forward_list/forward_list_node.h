#pragma once

namespace DataStructure::forward_list
{
    template <typename T>
    class ForwardListNode
    {
        typedef ForwardListNode<T> Node;
    public:
        ForwardListNode() = delete;
        ForwardListNode(const T & value) : m_value(value), m_next(nullptr) {}
        ~ForwardListNode() {}

    public:
        T m_value;
        Node * m_next;
    };
}
