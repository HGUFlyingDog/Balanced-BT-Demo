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
		if (root == nullptr) return ;
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
				cout << "插入" << key << "失败，因为有重复的节点"<<endl;
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
		
		this->print();
	}

	

private:
	Node* _root = nullptr; // 根节点指针
};


//std::ostream& operator<<(std::ostream& out, const AVLTree& Tree)//写个运算符重载函数练习一下
//{
//	tree.print(out);
//	return out;
//}