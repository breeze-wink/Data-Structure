#pragma once

#include "../tree_node.h"

namespace DataStructure
{
    template <typename T>
    class BSTreeNode : public TreeNode<T>
    {
    public:
        BSTreeNode() = delete;
        BSTreeNode(const T & key) : TreeNode<T>(key) {}
        virtual ~BSTreeNode() {}
    };
}
