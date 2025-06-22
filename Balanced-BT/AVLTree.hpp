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
	 
	//����һ��ֵ
	void insert(int key)
	{
		cout << "���ڲ���Ľڵ��ǣ�" << key << endl;
		if (_root == nullptr)
		{
			_root = new Node(key);
			return;
		}
		Node* cur = _root;
		Node* prev = cur;

		while (cur != nullptr)
		{
			if (key < cur->_key)// �������
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)// ���Ҳ���
			{
				prev = cur;
				cur = cur->_right;

			}
			else
			{
				cout << "����" << key << "ʧ�ܣ���Ϊ���ظ��Ľڵ�"<<endl;
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
	Node* _root = nullptr; // ���ڵ�ָ��
};


//std::ostream& operator<<(std::ostream& out, const AVLTree& Tree)//д����������غ�����ϰһ��
//{
//	tree.print(out);
//	return out;
//}