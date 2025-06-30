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
		if (other._root == nullptr) return; // 另一棵树为空，无需合并

		// 1. 将另一棵树的所有节点值提取到数组中
		std::vector<int> values;
		extractValues(other._root, values);

		// 2. 清空另一棵树
		other.clear();

		// 3. 将提取的值插入到当前树中
		for (int key : values) {
			insert(key);
		}
	}
	// 打印树结构（中序遍历）
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

	// 插入节点
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
				cout << "插入" << key << "失败，节点已存在" << endl;
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

		// 更新平衡因子
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

	// 删除节点
	bool remove(int key) {
		Node* node = findNode(key);
		if (!node) {
			cout << "未找到节点: " << key << endl;
			return false;
		}
		removeNode(node);
		return true;
	}

	// 打印树结构
	void printTree() {
		if (_root == nullptr) {
			cout << "空树" << endl;
			return;
		}
		_printTree(_root, 0);
	}

	// 查找节点
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

	// 清空树
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

	// 左旋
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

		// 更新平衡因子
		parent->_bf = 0;
		cur->_bf = 0;
	}

	// 右旋
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

		// 更新平衡因子
		parent->_bf = 0;
		cur->_bf = 0;
	}

	// 先左旋后右旋
	void RotateLR(Node* parent) {
		Node* Lchild = parent->_left;
		Node* LRchild = Lchild->_right;
		int bf = LRchild->_bf;

		// 先左旋左子树
		RotateL(Lchild);
		// 再右旋父节点
		RotateR(parent);

		// 更新平衡因子
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

	// 先右旋后左旋
	void RotateRL(Node* parent) {
		Node* Rchild = parent->_right;
		Node* RLchild = Rchild->_left;
		int bf = RLchild->_bf;

		// 先右旋右子树
		RotateR(Rchild);
		// 再左旋父节点
		RotateL(parent);

		// 更新平衡因子
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

	// 删除节点核心实现
	void removeNode(Node* node) {
		Node* parent = node->_parent;

		// 情况1: 叶子节点
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
		// 情况2: 只有右子树
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
		// 情况3: 只有左子树
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
		// 情况4: 有两个子节点
		else {
			// 找到后继节点
			Node* successor = node->_right;
			while (successor->_left != nullptr) {
				successor = successor->_left;
			}

			// 保存后继节点的值和平衡因子
			int successorKey = successor->_key;
			int successorBf = successor->_bf;

			// 递归删除后继节点
			removeNode(successor);

			// 替换当前节点的值
			node->_key = successorKey;
		}
	}

	// 向上平衡
	void balanceUpward(Node* node) {
		Node* parent = node;
		while (parent) {
			if (abs(parent->_bf) == 1) {
				// 高度不变，停止回溯
				break;
			}
			else if (parent->_bf == 0) {
				// 继续向上回溯
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
				// 需要旋转
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

				// 旋转后父节点可能改变
				parent = parent->_parent;
				if (parent && parent->_bf == 0) {
					// 继续向上回溯
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

	// 打印树结构（辅助函数）
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

	// 清空树（辅助函数）
	void _clear(Node* node) {
		if (node == nullptr) return;
		_clear(node->_left);
		_clear(node->_right);
		delete node;
	}
};