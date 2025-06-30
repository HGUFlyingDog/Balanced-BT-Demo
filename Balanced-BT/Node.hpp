#pragma once
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

// 在污染全局命名空间和简化代码之间取得平衡

// 先不考虑模板，专注于int类型


class Node
{
    friend class AVLTree;// 这里使用了友元函数保证AVLTree类可以访问我的Node的私有成员
public:
    Node(int key)
        :_key(key), _left(nullptr), _right(nullptr), _bf(0),_parent(nullptr)
    {
    }

private:
    int _key;            // 键（节点存储的值）
    Node* _left;         // 左子树指针
    Node* _right;        // 右子树指针
    Node* _parent;       // 父节点指针
    int _bf;             // 平衡因子（左高+1，右高-1，平衡0）
};

