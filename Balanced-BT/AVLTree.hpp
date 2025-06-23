#pragma once
#include<iostream>
#include"Node.hpp"

class AVLTree
{
public:
	AVLTree() {};
	~AVLTree() {};

	void printInOrder(const Node* root)
	{
		if (root == nullptr) return;
		printInOrder(root->_left);
		cout << root->_key << " ";
		printInOrder(root->_right);
	}

	void print()
	{
		printInOrder(_root);
		cout << endl;
	}

	//插入一个值
	void insert(int key)
	{
		cout << "现在插入的节点是：" << key << endl;
		if (_root == nullptr)
		{
			_root = new Node(key);
			return;
		}
		Node* cur = _root;
		Node* prev = cur;

		while (cur != nullptr)
		{
			if (key < cur->_key)// 向左插入
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)// 向右插入
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				cout << "插入" << key << "失败，因为有重复的节点" << endl;
				return;
			}
		}
		cur = new Node(key);
		if (key < prev->_key)
		{
			prev->_left = cur;
		}
		if (key > prev->_key)
		{
			prev->_right = cur;
		}

		cur->_parent = prev;
		this->print();

		// 控制平衡
		// 更新平衡因子
		// 最坏情况下更新到根节点
		while (prev)
		{
			if (cur == prev->_left)
			{
				prev->_bf++;
			}
			else
			{
				prev->_bf--;
			}

			if (prev->_bf == 0)  return;//更新结束 节点已经平衡
			if (abs(prev->_bf) == 1)
			{
				//继续向上更新
				prev = prev->_parent;
			}
			else if (abs(prev->_bf) == 2)
			{
				// 子树出现问题需要旋转
				// 左旋 RR 对应的 特点是失衡节点的平衡因子是-2，失衡节点的右孩子的平衡因子是-1
				if (true)
				{
					RotateL(prev);
				}
			}
			else
			{
				throw"平衡因子出现问题";
			}
		}
	}

private:
	Node* _root = nullptr; // 根节点指针

	void RotateL(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		parent->_right = cur->_left;//冲突的左孩子变成右孩子
		cur->_left = parent; 
		parent->_parent = cur; // 旋转 cur的左孩子变成原来的parent
		if (curleft != nullptr)
		{
			curleft->_parent = parent;// 原来的左孩子的父亲变成parent 加了一个判断防止越界访问
		}

		if (pparent != nullptr)// 传入节点的父节点指向旋转子树的父节点
		{
			if (parent== pparent->_left)
			{
				pparent->_left = cur;
			}
			else
			{
				pparent->_right = cur;
			}
			cur->_parent = pparent;// 旋转子树的父节点指向原来的父节点
		}

		
	}
};