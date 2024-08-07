#pragma once

#include <iostream>
#include "tree_node.h"
#include "tree_iterator.h"
#include "tree_const_iterator.h"
#include "tree_reverse_iterator.h"

namespace DataStructure
{
    template <typename T>
    class Tree
    {
        friend class Digraph;
        typedef TreeNode<T> Node;
    public:
        typedef TreeIterator<T> iterator;
        typedef TreeConstIterator<T> const_iterator;
        typedef TreeReverseIterator<T> reverse_iterator;
    public:
        Tree();
        virtual ~Tree();

        virtual void insert(const T & key) = 0;       // 插入
        virtual void remove(const T & key) = 0;       // 删除
        bool search(const T & key);                   // 查找
        int size() const;
        bool empty() const;
        bool valid() const;
        void clear();
        void swap(Tree<T> & other);
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const T & key);

    protected:
        bool valid(Node * root) const;
        bool search(Node * root, const T & key);        // 递归查找
        void clear(Node * root);                        // 递归清空
        void preorder(Node * root) const;               // 前序遍历
        void inorder(Node * root) const;                // 中序遍历
        void postorder(Node * root) const;              // 后序遍历

        virtual Node * create_node(const T & key) = 0;
        virtual void delete_node(Node * node) = 0;

    protected:
        Node * m_root;
        int m_size;
    };


    template <typename T> 
    Tree<T>::Tree() : m_root(nullptr), m_size(0) {}

    template <typename T>
    Tree<T>::~Tree()
    {
        clear();
    }

    template <typename T>
    bool Tree<T>::search(const T & key)
    {
        return search(m_root, key);
    }

    template <typename T>
    bool Tree<T>::valid(Node * root) const
    {
        if (root == nullptr)
            return true;
        if (root->m_left == nullptr && root->m_right == nullptr)
            return true;
        if (root->m_left != nullptr && root->m_right == nullptr)
        {
            if (root->m_key < root->m_left->m_key)
                return false;
            if (root->m_left->m_parent != root)
                return false;
            return valid(root->m_left);
        }
        else if (root->m_left == nullptr && root->m_right != nullptr)
        {
            if (root->m_key > root->m_right->m_key)
                return false;
            if (root->m_right->m_parent != root)
                return false;
            return valid(root->m_right);
        }
        else
        {
            if (root->m_key < root->m_left->m_key)
                return false;
            if (root->m_left->m_parent != root)
                return false;
            if (root->m_key > root->m_right->m_key)
                return false;
            if (root->m_right->m_parent != root)
                return false;
            return valid(root->m_left) && valid(root->m_right);
        }
    }

    template <typename T>
    bool Tree<T>::search(Node * root, const T & key)
    {
        if (root == nullptr)
            return false;
        if (root->m_key > key)
            return search(root->m_left, key);
        else if (root->m_key < key)
            return search(root->m_right, key);
        return true;
    }

    template <typename T>
    int Tree<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    bool Tree<T>::empty() const
    {
        return m_size == 0;
    }

    template <typename T>
    bool Tree<T>::valid() const
    {
        return valid(m_root);
    }

    template <typename T>
    void Tree<T>::clear()
    {
        clear(m_root);
        m_root = nullptr;
        m_size = 0;
    }

    template <typename T>
    void Tree<T>::swap(Tree<T> & other)
    {
        if (this == &other)
        {
            return;
        }
        auto root = other.m_root;
        int size = other.m_size;
        other.m_root = m_root;
        other.m_size = m_size;
        m_root = root;
        m_size = size;
    }

    template <typename T>
    void Tree<T>::clear(Node * root)
    {
        if (root == nullptr)
            return;
        clear(root->m_left);
        clear(root->m_right);
        delete root;
    }

    template <typename T>
    typename Tree<T>::iterator Tree<T>::begin()
    {
        if (m_root == nullptr)
            return end();
        return iterator(m_root, m_root->leftmost());
    }

    template <typename T>
    typename Tree<T>::iterator Tree<T>::end()
    {
        return iterator(m_root, nullptr);
    }

    template <typename T>
    typename Tree<T>::iterator Tree<T>::find(const T & key)
    {
        if (m_root == nullptr)
            return end();
        auto node = m_root->search(key);
        return iterator(m_root, node);
    }

    template <typename T>
    typename Tree<T>::const_iterator Tree<T>::cbegin() const
    {
        if (m_root == nullptr)
            return cend();
        return const_iterator(m_root, m_root->leftmost());
    }

    template <typename T>
    typename Tree<T>::const_iterator Tree<T>::cend() const
    {
        return const_iterator(m_root, nullptr);
    }

    template <typename T>
    typename Tree<T>::const_iterator Tree<T>::find(const T & key) const
    {
        if (m_root == nullptr)
            return cend();
        auto node = m_root->search(key);
        return const_iterator(m_root, node);
    }

    template <typename T>
    typename Tree<T>::reverse_iterator Tree<T>::rbegin()
    {
        if (m_root == nullptr)
            return rend();
        return reverse_iterator(m_root, m_root->rightmost());
    }

    template <typename T>
    typename Tree<T>::reverse_iterator Tree<T>::rend()
    {
        return reverse_iterator(m_root, nullptr);
    }

    template <typename T>
    typename Tree<T>::reverse_iterator Tree<T>::rfind(const T & key)
    {
        if (m_root == nullptr)
            return rend();
        auto node = m_root->search(key);
        return reverse_iterator(m_root, node);
    }

    template <typename T>
    void Tree<T>::show() const
    {
        std::cout << "size=" << m_size << std::endl;
        inorder(m_root);
        std::cout << std::endl;
    }

    template <typename T>
    void Tree<T>::preorder(Node * root) const
    {
        if (root == nullptr)
            return;
        std::cout << root->m_key << ", ";
        preorder(root->m_left);
        preorder(root->m_right);
    }

    template <typename T>
    void Tree<T>::inorder(Node * root) const
    {
        if (root == nullptr)
            return;
        inorder(root->m_left);
        std::cout << root->m_key << ", ";
        inorder(root->m_right);
    }

    template <typename T>
    void Tree<T>::postorder(Node * root) const
    {
        if (root == nullptr)
            return;
        inorder(root->m_left);
        inorder(root->m_right);
        std::cout << root->m_key << ", ";
    }

}
