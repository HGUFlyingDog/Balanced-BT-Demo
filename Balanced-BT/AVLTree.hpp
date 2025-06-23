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
				cout << "����" << key << "ʧ�ܣ���Ϊ���ظ��Ľڵ�" << endl;
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

		// ����ƽ��
		// ����ƽ������
		// �����¸��µ����ڵ�
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

			if (prev->_bf == 0)  return;//���½��� �ڵ��Ѿ�ƽ��
			if (abs(prev->_bf) == 1)
			{
				//�������ϸ���
				prev = prev->_parent;
			}
			else if (abs(prev->_bf) == 2)
			{
				// ��������������Ҫ��ת
				// ���� RR ��Ӧ�� �ص���ʧ��ڵ��ƽ��������-2��ʧ��ڵ���Һ��ӵ�ƽ��������-1
				if (true)
				{
					RotateL(prev);
				}
			}
			else
			{
				throw"ƽ�����ӳ�������";
			}
		}
	}

private:
	Node* _root = nullptr; // ���ڵ�ָ��

	void RotateL(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		parent->_right = cur->_left;//��ͻ�����ӱ���Һ���
		cur->_left = parent; 
		parent->_parent = cur; // ��ת cur�����ӱ��ԭ����parent
		if (curleft != nullptr)
		{
			curleft->_parent = parent;// ԭ�������ӵĸ��ױ��parent ����һ���жϷ�ֹԽ�����
		}

		if (pparent != nullptr)// ����ڵ�ĸ��ڵ�ָ����ת�����ĸ��ڵ�
		{
			if (parent== pparent->_left)
			{
				pparent->_left = cur;
			}
			else
			{
				pparent->_right = cur;
			}
			cur->_parent = pparent;// ��ת�����ĸ��ڵ�ָ��ԭ���ĸ��ڵ�
		}

		
	}
};