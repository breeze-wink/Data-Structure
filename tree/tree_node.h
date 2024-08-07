#pragma once

namespace DataStructure
{
    template <typename T>
    class TreeNode
    {
        typedef TreeNode<T> Node;
    public:
        TreeNode() = delete;
        TreeNode(const T & key) : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_key(key) {}
        virtual ~TreeNode() {}

        Node * search(const T & key);
        Node * leftmost();
        Node * rightmost();
        Node * predecessor();
        Node * successor();

    public:
        Node * m_parent;
        Node * m_left;
        Node * m_right;
        T m_key;
    };

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::search(const T & key)
    {
        auto node = this;
        while (node != nullptr)
        {
            if (node->m_key == key)
                break;
            else if (node->m_key > key)
                node = node->m_left;
            else
                node = node->m_right;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::leftmost()
    {
        // find the leftmost leaf node
        auto node = this;
        while (node != nullptr)
        {
            if (node->m_left == nullptr)
            {
                break;
            }
            node = node->m_left;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::rightmost()
    {
        // find the rightmost leaf node
        Node * node = this;
        while (node != nullptr)
        {
            if (node->m_right == nullptr)
            {
                break;
            }
            node = node->m_right;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::predecessor() //寻找前驱节点
    {
        if (m_left != nullptr)
            return m_left->rightmost();

        auto node = m_parent;
        while (node != nullptr)
        {
            if (node -> m_key < m_key)
            {
                break;
            }
            node = node->m_parent;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::successor() //后继节点
    {
        if (m_right != nullptr)
            return m_right->leftmost();

        auto node = m_parent;
        while (node != nullptr)
        {
            if (node->m_key > m_key)
            {
                break;
            }
            node = node->m_parent;
        }
        return node;
    }
}
