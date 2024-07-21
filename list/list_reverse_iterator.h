#include "list_node.h"

namespace DataStructure::list
{
    template <typename T>
    class ListReverseIterator
    {
        typedef ListNode<T> Node;
        typedef ListReverseIterator<T> iterator;
    public:
        ListReverseIterator() : m_pointer(nullptr) {}
        ListReverseIterator(Node * pointer) : m_pointer(pointer) {}
        ~ListReverseIterator() {}

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
            m_pointer = m_pointer -> m_prev;
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
                it.m_pointer = it.m_pointer -> m_prev;
            }
            return it;
        }

        iterator & operator += (int n)
        {
            for (int i = 0; i < n; i++)
            {
                m_pointer = m_pointer -> m_prev;
            }
            return *this;
        }

        iterator & operator -- ()
        {
            m_pointer = m_pointer -> m_next;
            return *this;
        }

        iterator operator -- (int)
        {
            iterator it = *this;
            --(*this);
            return it;
        }

        iterator operator - (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                it.m_pointer = it.m_pointer -> m_next;
            }
            return it;
        }

        iterator & operator -= (int n)
        {
            for (int i = 0; i < n; i++)
            {
                m_pointer = m_pointer -> m_next;
            }
            return *this;
        }

        T & operator * ()
        {
            return m_pointer -> m_value;
        }

        T * operator  ->  ()
        {
            return &(m_pointer -> m_value);
        }

    private:
        Node * m_pointer;
    };
}
