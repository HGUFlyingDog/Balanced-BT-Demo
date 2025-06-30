#pragma once
#include<iostream>
#include"Node.hpp"
#include<vector>

class AVLTree
{
public:
	AVLTree() {};

	~AVLTree() {
		clear();
	};

	void splitTree( int x)
	{
		AVLTree tree1;
		AVLTree tree2;
		std::vector<int> key;
		extractValues(_root, key);

		for (auto ch : key)
		{
			cout << ch << " ";
		}
		cout << endl;

		for (auto ch : key)
		{
			if (x < ch)
			{
				tree1.insert(ch);
			}
			else
			{
				tree2.insert(ch);
			}
		}

		cout << "tree1:" << endl;
		tree1.printTree();

		cout << endl << endl << endl << endl;
		cout << "tree2:" << endl;

		tree2.printTree();

	}

	void merge(AVLTree& other) {
		if (other._root == nullptr) return; // ��һ����Ϊ�գ�����ϲ�

		// 1. ����һ���������нڵ�ֵ��ȡ��������
		std::vector<int> values;
		extractValues(other._root, values);

		// 2. �����һ����
		other.clear();

		// 3. ����ȡ��ֵ���뵽��ǰ����
		for (int key : values) {
			insert(key);
		}
	}
	// ��ӡ���ṹ�����������
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

	// ����ڵ�
	void insert(int key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return;
		}

		Node* cur = _root;
		Node* prev = cur;

		while (cur != nullptr)
		{
			prev = cur;
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				cout << "����" << key << "ʧ�ܣ��ڵ��Ѵ���" << endl;
				return;
			}
		}

		cur = new Node(key);
		cur->_parent = prev;

		if (key < prev->_key)
		{
			prev->_left = cur;
		}
		else
		{
			prev->_right = cur;
		}

		// ����ƽ������
		Node* parent = prev;
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}

			if (parent->_bf == 0)
			{
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == 2)
				{
					if (parent->_left->_bf == 1)
					{
						RotateR(parent);
					}
					else
					{
						RotateLR(parent);
					}
				}
				else
				{
					if (parent->_right->_bf == -1)
					{
						RotateL(parent);
					}
					else
					{
						RotateRL(parent);
					}
				}
				break;
			}
		}
	}

	// ɾ���ڵ�
	bool remove(int key) {
		Node* node = findNode(key);
		if (!node) {
			cout << "δ�ҵ��ڵ�: " << key << endl;
			return false;
		}
		removeNode(node);
		return true;
	}

	// ��ӡ���ṹ
	void printTree() {
		if (_root == nullptr) {
			cout << "����" << endl;
			return;
		}
		_printTree(_root, 0);
	}

	// ���ҽڵ�
	Node* findNode(int key) {
		Node* cur = _root;
		while (cur) {
			if (key < cur->_key) {
				cur = cur->_left;
			}
			else if (key > cur->_key) {
				cur = cur->_right;
			}
			else {
				return cur;
			}
		}
		return nullptr;
	}

	// �����
	void clear()
	{
		_clear(_root);
		_root = nullptr;
	}

private:
	Node* _root = nullptr;

	void extractValues(Node* node, std::vector<int>& values) {
		if (node == nullptr) return;
		extractValues(node->_left, values);
		values.push_back(node->_key);
		extractValues(node->_right, values);
	}

	// ����
	void RotateL(Node* parent) {
		Node* pparent = parent->_parent;
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		parent->_right = curleft;
		if (curleft) {
			curleft->_parent = parent;
		}

		cur->_left = parent;
		parent->_parent = cur;

		if (pparent) {
			if (pparent->_left == parent) {
				pparent->_left = cur;
			}
			else {
				pparent->_right = cur;
			}
			cur->_parent = pparent;
		}
		else {
			_root = cur;
			cur->_parent = nullptr;
		}

		// ����ƽ������
		parent->_bf = 0;
		cur->_bf = 0;
	}

	// ����
	void RotateR(Node* parent) {
		Node* pparent = parent->_parent;
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		parent->_left = curright;
		if (curright) {
			curright->_parent = parent;
		}

		cur->_right = parent;
		parent->_parent = cur;

		if (pparent) {
			if (pparent->_left == parent) {
				pparent->_left = cur;
			}
			else {
				pparent->_right = cur;
			}
			cur->_parent = pparent;
		}
		else {
			_root = cur;
			cur->_parent = nullptr;
		}

		// ����ƽ������
		parent->_bf = 0;
		cur->_bf = 0;
	}

	// ������������
	void RotateLR(Node* parent) {
		Node* Lchild = parent->_left;
		Node* LRchild = Lchild->_right;
		int bf = LRchild->_bf;

		// ������������
		RotateL(Lchild);
		// ���������ڵ�
		RotateR(parent);

		// ����ƽ������
		if (bf == 1) {
			parent->_bf = -1;
			Lchild->_bf = 0;
		}
		else if (bf == -1) {
			parent->_bf = 0;
			Lchild->_bf = 1;
		}
		else {
			parent->_bf = 0;
			Lchild->_bf = 0;
		}
		LRchild->_bf = 0;
	}

	// ������������
	void RotateRL(Node* parent) {
		Node* Rchild = parent->_right;
		Node* RLchild = Rchild->_left;
		int bf = RLchild->_bf;

		// ������������
		RotateR(Rchild);
		// ���������ڵ�
		RotateL(parent);

		// ����ƽ������
		if (bf == 1) {
			parent->_bf = 0;
			Rchild->_bf = -1;
		}
		else if (bf == -1) {
			parent->_bf = 1;
			Rchild->_bf = 0;
		}
		else {
			parent->_bf = 0;
			Rchild->_bf = 0;
		}
		RLchild->_bf = 0;
	}

	// ɾ���ڵ����ʵ��
	void removeNode(Node* node) {
		Node* parent = node->_parent;

		// ���1: Ҷ�ӽڵ�
		if (node->_left == nullptr && node->_right == nullptr) {
			if (parent) {
				if (parent->_left == node) {
					parent->_left = nullptr;
					parent->_bf--;
				}
				else {
					parent->_right = nullptr;
					parent->_bf++;
				}
			}
			else {
				_root = nullptr;
			}
			delete node;
			balanceUpward(parent);
		}
		// ���2: ֻ��������
		else if (node->_left == nullptr) {
			Node* child = node->_right;
			if (parent) {
				if (parent->_left == node) {
					parent->_left = child;
					parent->_bf--;
				}
				else {
					parent->_right = child;
					parent->_bf++;
				}
				child->_parent = parent;
			}
			else {
				_root = child;
				child->_parent = nullptr;
			}
			delete node;
			balanceUpward(parent);
		}
		// ���3: ֻ��������
		else if (node->_right == nullptr) {
			Node* child = node->_left;
			if (parent) {
				if (parent->_left == node) {
					parent->_left = child;
					parent->_bf--;
				}
				else {
					parent->_right = child;
					parent->_bf++;
				}
				child->_parent = parent;
			}
			else {
				_root = child;
				child->_parent = nullptr;
			}
			delete node;
			balanceUpward(parent);
		}
		// ���4: �������ӽڵ�
		else {
			// �ҵ���̽ڵ�
			Node* successor = node->_right;
			while (successor->_left != nullptr) {
				successor = successor->_left;
			}

			// �����̽ڵ��ֵ��ƽ������
			int successorKey = successor->_key;
			int successorBf = successor->_bf;

			// �ݹ�ɾ����̽ڵ�
			removeNode(successor);

			// �滻��ǰ�ڵ��ֵ
			node->_key = successorKey;
		}
	}

	// ����ƽ��
	void balanceUpward(Node* node) {
		Node* parent = node;
		while (parent) {
			if (abs(parent->_bf) == 1) {
				// �߶Ȳ��䣬ֹͣ����
				break;
			}
			else if (parent->_bf == 0) {
				// �������ϻ���
				Node* grandparent = parent->_parent;
				if (grandparent) {
					if (parent == grandparent->_left) {
						grandparent->_bf--;
					}
					else {
						grandparent->_bf++;
					}
				}
				parent = grandparent;
			}
			else if (abs(parent->_bf) == 2) {
				// ��Ҫ��ת
				if (parent->_bf == 2) {
					if (parent->_left->_bf >= 0) {
						RotateR(parent);
					}
					else {
						RotateLR(parent);
					}
				}
				else if (parent->_bf == -2) {
					if (parent->_right->_bf <= 0) {
						RotateL(parent);
					}
					else {
						RotateRL(parent);
					}
				}

				// ��ת�󸸽ڵ���ܸı�
				parent = parent->_parent;
				if (parent && parent->_bf == 0) {
					// �������ϻ���
					Node* grandparent = parent->_parent;
					if (grandparent) {
						if (parent == grandparent->_left) {
							grandparent->_bf--;
						}
						else {
							grandparent->_bf++;
						}
					}
					parent = grandparent;
				}
				else {
					break;
				}
			}
		}
	}

	// ��ӡ���ṹ������������
	void _printTree(Node* node, int depth) {
		if (!node) return;

		_printTree(node->_right, depth + 1);

		for (int i = 0; i < depth; i++)
			cout << "    ";
		cout << node->_key << " (bf:" << node->_bf << ")";

		if (node == _root)
			cout << " [root]";
		else if (!node->_left && !node->_right)
			cout << " [leaf]";

		cout << endl;

		_printTree(node->_left, depth + 1);
	}

	// �����������������
	void _clear(Node* node) {
		if (node == nullptr) return;
		_clear(node->_left);
		_clear(node->_right);
		delete node;
	}
};