#pragma once
#include<iostream>
#include"Node.hpp"

class AVLTree
{
public:
	AVLTree() {};
	
	~AVLTree() {};


	// �ݹ���ʽ�Ĵ�ӡ�ṹ������û�а취ʹ��thisָ�봫��ʵ�֣�����ʹ��print������������ڵ㣬����ʹ�õ�����������������������������൱�ڴ�С�����ӡ���������ڿ����ж������������Ľ����Ƿ�ɹ�
	void printInOrder(const Node* root)
	{
		if (root == nullptr) return;// ��ֹ����
		printInOrder(root->_left);// �ݹ����������
		cout << root->_key << " "; // ��ӡ
		printInOrder(root->_right);// �ݹ����������
	}

	//������ǵ���printInOrder�ĺ�����ʹ��thisָ��Ȼ������ڵ��ָ��
	void print()
	{
		printInOrder(_root);
		cout << endl;
	}

	//����һ��ֵ����������һ��int ���͵ļ�ֵ��Ȼ������������ǲ��������ֵ���ұ��������������ƽ��
	void insert(int key)
	{
		cout << "���ڲ���Ľڵ��ǣ�" << key << endl;
		if (_root == nullptr)//�����ڴ����ڵ�ʱ��ĳ�ʼ�����֣�����ǿյĽڵ�Ͷ�̬����һ��
		{
			_root = new Node(key);
			return;
		}
		// ����ʹ��һ��cur��ʾ��ǰ�ڵ��һ��prev��ʾ��ǰ�ڵ��ǰһ���ڵ㷽���������Ĳ���
		// ���Ǻ��������ҶԴ����������룬����Node����������һ��parent����ʾprev�����ڰ���������Ż�һ�±�ø��Ӽ��
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
			else// �ҵĶ���������Ŀǰ��֧����ͬ�ؼ��ֵĲ��룬��Ȼ�Ƿ����룬���ǲ��������쳣
			{
				cout << "����" << key << "ʧ�ܣ���Ϊ���ظ��Ľڵ�" << endl;
				return;
			}
		}

		cur = new Node(key);// ��������ҵ��˲���Ĳ��֣��½��ڵ�Ȼ��ʼ���룬���õ���Node�Ĺ��캯��
		if (key < prev->_key)
		{
			prev->_left = cur;
		}
		if (key > prev->_key)
		{
			prev->_right = cur;
		}

		cur->_parent = prev;
		this->print();//����һ�²���Ľ��

		// ����ƽ��
		// ����ƽ������
		// �����¸��µ����ڵ�
		while (prev)
		{
			//����ж�������Ŀ�ľ���
			// 1. �����������룬parentƽ������++
			// 2. �����������룬parentƽ������--

			if (cur == prev->_left)
			{
				prev->_bf++;
			}
			else
			{
				prev->_bf--;
			}

			if (prev->_bf == 0)  return;//���½��� �ڵ��Ѿ�ƽ�⣬����������Ӱ�츸�ڵ���
			if (abs(prev->_bf) == 1)
			{
				//�������ϸ���
				cur = prev;
				prev = prev->_parent;

			}
			//else if (abs(prev->_bf) == 2)
			//{
			//	// ��������������Ҫ��ת
			//	// ���� RR ��Ӧ�� �ص���ʧ��ڵ��ƽ��������-2��ʧ��ڵ���Һ��ӵ�ƽ��������-1
			//	if (prev->_bf == -2 && prev->_right->_bf == -1)// RR
			//	{
			//		RotateL(prev);
			//	}
			//	else if (prev->_bf == 2 && prev->_right->_bf == 1)// LL
			//	{
			//		RotateR(prev);
			//	}
			//	else if (prev->_bf == 2 && prev->_right->_bf == -1)// LR
			//	{
			//		RotateLR(prev);
			//	}
			//	else if (prev->_bf == -2 && prev->_right->_bf == 1)// RL
			//	{
			//		RotateRL(prev);
			//	}
			//	break;
			//}

			else if (abs(prev->_bf) == 2)
			{
				// ����ʵ���ӽڵ��ж���ת����
				if (prev->_bf == -2)
				{
					if (prev->_right->_bf == -1) // RR
					{
						RotateL(prev);
					}
					else if (prev->_right->_bf == 1) // RL
					{
						RotateRL(prev);
					}
				}
				else if (prev->_bf == 2)
				{
					if (prev->_left->_bf == 1) // LL
					{
						RotateR(prev);
					}
					else if (prev->_left->_bf == -1) // LR
					{
						RotateLR(prev);
					}
				}
				break; // ��ת���˳�ѭ��
			}
			else//ƽ�����Ӳ�����������ֵ�������֣�ֱ�����쳣���ҵĳ����д��bug
			{
				throw"ƽ�����ӳ�������";
			}
		}
	}

	// ɾ���ڵ㲢ά��ƽ��
	

private:
	Node* _root = nullptr; // ���ڵ�ָ��


	// ������������Ĳ���,Ҫ����һ��Node*�Ľڵ�ʵʩ��ת���ܣ�������ǲ��ֵĽṹ����ת��
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
			if (parent == pparent->_left)
			{
				pparent->_left = cur;
			}
			else
			{
				pparent->_right = cur;
			}
			cur->_parent = pparent;// ��ת�����ĸ��ڵ�ָ��ԭ���ĸ��ڵ�
		}

		else
		{
			_root = cur; // ���¸��ڵ�
			cur->_parent = nullptr;
		}

		cur->_bf = parent->_bf = 0;
	}


	//������������Ĳ�������������࣬����˳��һ�£�Ҫ����һ��Node*�Ľڵ�ʵʩ��ת���ܣ�������ǲ��ֵĽṹ����ת��
	void RotateR(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		parent->_left = curright;
		cur->_right = parent;
		if (curright != nullptr)
		{
			curright->_parent = parent;
		}
		parent->_parent = cur;

		if (pparent != nullptr)
		{
			if (parent == pparent->_left)
			{
				cur = pparent->_left;
			}
			else
			{
				cur = pparent->_right;
			}
			cur->_parent = pparent;

		}

		if (pparent == nullptr) {
			_root = cur; // ���¸��ڵ�
			cur->_parent = nullptr;
		}
		cur->_bf = parent->_bf = 0;
	}

	// �������Ƕ������Һ���Ȼ��������Ҫ����һ��Node*�Ľڵ�ʵʩ��ת���ܣ������������������Ѿ�ƽ����
	void RotateRL(Node* parent)
	{
		Node* Rchild = parent->_right;
		Node* RLchild = Rchild->_left;

		// �ȶ��Һ�������
		RotateR(Rchild);
		// �ٶ�parent����
		RotateL(parent);

		// ��ת��ƽ�����ӵĵ���
		// RLchild ��תǰ�� _bf ������ parent �� Rchild ���� _bf
		if (RLchild->_bf == 1) {
			parent->_bf = 0;
			Rchild->_bf = -1;
		}
		else if (RLchild->_bf == -1) {
			parent->_bf = 1;
			Rchild->_bf = 0;
		}
		else { // RLchild->_bf == 0
			parent->_bf = 0;
			Rchild->_bf = 0;
		}
		RLchild->_bf = 0;
	}

	// �������Ƕ���������Ȼ��������Ҫ����һ��Node*�Ľڵ�ʵʩ��ת���ܣ������������������Ѿ�ƽ��
	void RotateLR(Node* parent)
	{
		Node* Lchild = parent->_left;
		Node* LRchild = Lchild->_right;

		// �ȶ���������
		RotateL(Lchild);
		// �ٶ�parent����
		RotateR(parent);

		// ��ת��ƽ�����ӵĵ���
		// ����LRchild��_bf����parent��Lchild��_bf
		if (LRchild->_bf == 1) {
			parent->_bf = 0;
			Lchild->_bf = -1;
		}
		else if (LRchild->_bf == -1) {
			parent->_bf = 1;
			Lchild->_bf = 0;
		}
		else { // LRchild->_bf == 0
			parent->_bf = 0;
			Lchild->_bf = 0;
		}
		LRchild->_bf = 0;
		
	}
};