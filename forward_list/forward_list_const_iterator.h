#pragma once

#include "forward_list_node.h"

namespace DataStructure
{
    template <typename T>
    class ForwardListConstIterator
    {
        typedef ForwardListNode<T> Node;
        typedef ForwardListConstIterator<T> iterator;
    public:
        ForwardListConstIterator() : m_pointer(nullptr) {}
        ForwardListConstIterator(Node * pointer) : m_pointer(pointer) {}
        virtual ~ForwardListConstIterator() {}

    public:
        bool operator == (const iterator & other)
        {
            return m_pointer == other.m_pointer;
        }

        bool operator != (const iterator & other)
        {
            return m_pointer != other.m_pointer;
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_pointer = other.m_pointer;
            return *this;
        }

        iterator & operator ++ ()
        {
            m_pointer = m_pointer -> m_next;
            return *this;
        }

        iterator operator ++ (int)
        {
            iterator it = *this;
            ++(*this);
            return it;
        }

        iterator operator + (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                ++it;
            }
            return it;
        }

        iterator & operator += (int n)
        {
            for (int i = 0; i < n; i++)
            {
                ++(*this);
            }
            return *this;
        }

        const T & operator * ()
        {
            return m_pointer -> m_value;
        }

        const T * operator  ->  ()
        {
            return &(m_pointer -> m_value);
        }

    private:
        Node * m_pointer;
    };
}
