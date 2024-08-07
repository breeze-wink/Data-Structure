#pragma once

#include "tree_node.h"

namespace DataStructure
{
    template <typename T>
    class TreeIterator
    {
        typedef TreeNode<T> Node;
        typedef TreeIterator<T> iterator;
    public:
        TreeIterator() : m_root(nullptr), m_pointer(nullptr) {}
        TreeIterator(Node * root, Node * pointer) : m_root(root), m_pointer(pointer) {}
        ~TreeIterator() {}

        bool operator == (const iterator & other)
        {
            return (m_root == other.m_root) && (m_pointer == other.m_pointer);
        }

        bool operator != (const iterator & other)
        {
            return (m_root != other.m_root) || (m_pointer != other.m_pointer);
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_root = other.m_root;
            m_pointer = other.m_pointer;
            return *this;
        }

        iterator & operator ++ ()
        {
            if (m_pointer == nullptr)
            {
                m_pointer = m_root->leftmost();
                return *this;
            }
            m_pointer = m_pointer->successor();
            return *this;
        }

        iterator operator ++ (int) //后向
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

        iterator & operator -- ()
        {
            if (m_pointer == nullptr)
            {
                m_pointer = m_root->rightmost();
                return *this;
            }
            m_pointer = m_pointer->predecessor();
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
                --it;
            }
            return it;
        }

        iterator & operator -= (int n)
        {
            for (int i = 0; i < n; i++)
            {
                --(*this);
            }
            return *this;
        }

        T & operator * ()
        {
            return m_pointer->m_key;
        }

        T * operator -> ()
        {
            return &(m_pointer->m_key);
        }

    private:
        Node * m_root;
        Node * m_pointer;
    };
}
