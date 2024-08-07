#pragma once

#include <iostream>
#include "../tree.h"
#include "bs_tree_node.h"

namespace DataStructure
{
    template <typename T>
    class BSTree : public Tree<T>
    {
        typedef BSTreeNode<T> Node;
    public:
        BSTree();
        virtual ~BSTree();

        virtual void insert(const T & key);             // 插入
        virtual void remove(const T & key);             // 删除

        virtual bool add(const T & key);                // 非递归插入
        virtual bool del(const T & key);                // 非递归删除

    protected:
        virtual TreeNode<T> * create_node(const T & key);
        virtual void delete_node(TreeNode<T> * node);

        // 递归操作
        virtual TreeNode<T> * insert(TreeNode<T> * root, const T & key);    // 递归插入
        virtual TreeNode<T> * remove(TreeNode<T> * root, const T & key);    // 递归删除

        virtual TreeNode<T> * left_rotate(TreeNode<T> * node);              // 左旋转
        virtual TreeNode<T> * right_rotate(TreeNode<T> * node);             // 右旋转

        // 非递归操作原始函数
        TreeNode<T> * add_raw(const T & key);
        TreeNode<T> * del_raw(const T & key);
    };

    template <typename T>
    BSTree<T>::BSTree() : Tree<T>() {}

    template <typename T>
    BSTree<T>::~BSTree() {}

    template <typename T>
    TreeNode<T> * BSTree<T>::create_node(const T & key)
    {
        auto node = new Node(key);
        this->m_size++;
        return node;
    }

    template <typename T>
    void BSTree<T>::delete_node(TreeNode<T> * node)
    {
        this->m_size--;
        delete node;
    }

    template <typename T>
    void BSTree<T>::insert(const T & key)
    {
        this->m_root = insert(this->m_root, key);
    }

    template <typename T>
    void BSTree<T>::remove(const T & key)
    {
        this->m_root = remove(this->m_root, key);
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::insert(TreeNode<T> * root, const T & key)
    {
        if (root == nullptr)
        {
            return create_node(key);
        }
        if (root->m_key > key)
        {
            root->m_left = insert(root->m_left, key);
            root->m_left->m_parent = root;
        }
        else if (root->m_key < key)
        {
            root->m_right = insert(root->m_right, key);
            root->m_right->m_parent = root;
        }
        else
        {
            return root;
        }
        return root;
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::remove(TreeNode<T> * root, const T & key)
    {
        if (root == nullptr)
            return nullptr;
        if (root->m_key > key)
        {
            root->m_left = remove(root->m_left, key);
            if (root->m_left != nullptr)
                root->m_left->m_parent = root;
        }
        else if (root->m_key < key)
        {
            root->m_right = remove(root->m_right, key);
            if (root->m_right != nullptr)
                root->m_right->m_parent = root;
        }
        else
        {
            if (root->m_left == nullptr) //no left child
            {
                auto r = root->m_right;
                if (r != nullptr)
                    r->m_parent = root->m_parent;
                delete_node(root);
                return r;
            }
            else if (root->m_right == nullptr) //no right child
            {
                auto l = root->m_left;
                if (l != nullptr)
                    l->m_parent = root->m_parent;
                delete_node(root);
                return l;
            }
            else
            {
                // if the node has two child
                auto node = root->successor();
                root->m_key = node->m_key; //直接修改key值为后继节点，然后再把后继节点删了
                root->m_right = remove(root->m_right, node->m_key);
            }
        }
        return root;
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::left_rotate(TreeNode<T> * node)
    {
        auto p = node->m_parent;
        auto x = node->m_right;
        auto y = x->m_left;
        x->m_left = node;
        node->m_parent = x;
        node->m_right = y;
        if (y != nullptr)
            y->m_parent = node;
        x->m_parent = p;
        if (p == nullptr)
        {
            this->m_root = x;
        }
        else
        {
            if (p->m_left == node)
                p->m_left = x;
            else
                p->m_right = x;
        }
        return x;
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::right_rotate(TreeNode<T> * node)
    {
        auto p = node->m_parent;
        auto x = node->m_left;
        auto y = x->m_right;
        x->m_right = node;
        node->m_parent = x;
        node->m_left = y;
        if (y != nullptr)
            y->m_parent = node;
        x->m_parent = p;
        if (p == nullptr)
        {
            this->m_root = x;
        }
        else
        {
            if (p->m_left == node)
                p->m_left = x;
            else
                p->m_right = x;
        }
        return x;
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::add_raw(const T & key)
    {
        auto root = this->m_root;
        TreeNode<T> * parent = nullptr;
        while (root != nullptr)
        {
            parent = root;
            if (root->m_key == key)
                return nullptr;
            if (key < root->m_key)
                root = root->m_left;
            else
                root = root->m_right;
        }//循环结束时parent为最后一个不为空的点

        auto node = create_node(key);
        if (this->m_root == nullptr)
        {
            this->m_root = node;
            return node;
        }
        if (key < parent->m_key)
        {
            parent->m_left = node;
            node->m_parent = parent;
        }
        else
        {
            parent->m_right = node;
            node->m_parent = parent;
        }
        return node;
    }

    template <typename T>
    TreeNode<T> * BSTree<T>::del_raw(const T & key) //找到要删的点，配合del函数
    {
        auto root = this->m_root;
        while (root != nullptr)
        {
            if (root->m_key > key)
                root = root->m_left;
            else if (root->m_key < key)
                root = root->m_right;
            else
                break;
        }

        if (root == nullptr)
        {
            // not found
            return nullptr;
        }

        if (root->m_left != nullptr && root->m_right != nullptr)
        {
            // if the node has two child, find the successor
            auto node = root->successor();
            root->m_key = node->m_key;
            root = node;
        }
        return root;
    }

    template <typename T>
    bool BSTree<T>::add(const T & key)
    {
        auto node = add_raw(key);
        if (node == nullptr)
            return false;
        return true;
    }

    template <typename T>
    bool BSTree<T>::del(const T & key)
    {
        auto node = del_raw(key);
        if (node == nullptr)
            return false;

        TreeNode<T> * repl = nullptr;
        if (node->m_left != nullptr && node->m_right == nullptr)
            repl = node->m_left;
        else if (node->m_left == nullptr && node->m_right != nullptr)
            repl = node->m_right;

        if (repl != nullptr)
            repl->m_parent = node->m_parent;
        if (node->m_parent == nullptr)
            this->m_root = repl;
        else
        {
            if (node == node->m_parent->m_left)
                node->m_parent->m_left = repl;
            else
                node->m_parent->m_right = repl;
        }
        delete_node(node);
        return true;
    }


}
