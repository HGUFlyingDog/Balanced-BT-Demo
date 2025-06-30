#pragma once
#include<iostream>
#include"Node.hpp"
#include<vector>

// AVL树（自平衡二叉搜索树）类定义
class AVLTree
{
public:
	AVLTree() {};

	~AVLTree() {
		clear(); // 析构时清空树
	};

	// 传入一个键值，根据键值分离两颗二叉树
	void splitTree(int x)
	{
		AVLTree tree1;
		AVLTree tree2;
		std::vector<int> key;
		extractValues(_root, key);// 导入二叉树的数值

		for (auto ch : key)
		{
			cout << ch << " ";
		}
		cout << endl;


		// 通过比较来传入数据
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

	// 合并另一棵AVL树到当前树
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
	// 递归形式的打印结构，这里没有办法使用this指针传参实现，所以使用print函数来传入根节点，这里使用的是中序遍历，在搜索二叉树就是相当于从小到大打印，方便我在快速判断搜索二叉树的建立是否成功
	void printInOrder(const Node* root)
	{
		if (root == nullptr) return;// 终止条件
		printInOrder(root->_left);// 递归调用左子树
		cout << root->_key << " "; // 打印
		printInOrder(root->_right);// 递归调用右子树
	}

	//这个就是调用printInOrder的函数，使用this指针然后传入根节点的指针
	void print()
	{
		printInOrder(_root);
		cout << endl;
	}

	//插入一个值，传参输入一个int 类型的键值，然后这个函数就是插入这个键值并且保持这个二叉树的平衡
	void insert(int key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key); // 空树直接插入根节点
			return;
		}
		// 这里使用一个cur表示当前节点和一个prev表示当前节点的前一个节点方便进行链表的插入
		Node* cur = _root;
		Node* prev = cur;

		// 查找插入位置
		while (cur != nullptr)
		{
			prev = cur;
			if (key < cur->_key)// 向左插入
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)// 向右插入
			{
				cur = cur->_right;
			}
			else// 我的二叉搜索树目前不支持相同关键字的插入，虽然非法插入，但是不至于抛异常
			{
				cout << "插入" << key << "失败，节点已存在" << endl;
				return;
			}
		}

		try
		{
			cur = new Node(key);// 这里就是找到了插入的部分，新建节点然后开始插入，调用的是Node的构造函数
		}
		catch (const std::exception& e)
		{
			std::cerr << "内存分配失败: " << e.what() << '\n';
			throw;
		}
		cur->_parent = prev;

		// 挂到父节点的左或右
		if (key < prev->_key)
		{
			prev->_left = cur;
		}
		else
		{
			prev->_right = cur;
		}

		// 更新平衡因子并自下而上调整、

		// 控制平衡
		// 更新平衡因子
		// 最坏情况下更新到根节点

		// 1. 在左子树插入，parent平衡因子++
		// 2. 在右子树插入，parent平衡因子--

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
				break; // 插入后高度未变，停止
			}
			else if (abs(parent->_bf) == 1)//更新结束 节点已经平衡，不会再往上影响父节点了
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
				// 子树出现问题需要旋转
				// 左旋 RR 对应的 特点是失衡节点的平衡因子是-2，失衡节点的右孩子的平衡因子是-1

			{
				if (parent->_bf == 2)
				{
					if (parent->_left->_bf == 1)
					{
						RotateR(parent); // LL型右旋
					}
					else
					{
						RotateLR(parent); // LR型先左后右
					}
				}
				else
				{
					if (parent->_right->_bf == -1)
					{
						RotateL(parent); // RR型左旋
					}
					else
					{
						RotateRL(parent); // RL型先右后左
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
		removeNode(node); // 删除节点并调整
		return true;
	}

	// 打印树结构（竖向）
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
	Node* _root = nullptr; // 根节点

	// 中序遍历提取所有节点值
	void extractValues(Node* node, std::vector<int>& values) {
		if (node == nullptr) return;
		extractValues(node->_left, values);
		values.push_back(node->_key);
		extractValues(node->_right, values);
	}

	// 左旋操作
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
			if (parent == pparent->_left)
			{
				pparent->_left = cur;
			}
			else
			{
				pparent->_right = cur;
			}
			cur->_parent = pparent;// 旋转子树的父节点指向原来的父节点
		}

		cur->_bf = parent->_bf = 0;
	}

	// 右旋操作
	//这个就是右旋的操作，跟左旋差不多，就是顺序换一下，要求传入一个Node*的节点实施旋转功能，结果就是部分的结构被旋转了
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

	// 先左旋后右旋（LR型）
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

	// 先右旋后左旋（RL型）
	// 操作就是对右旋右孩子然后左旋，要求传入一个Node*的节点实施旋转功能，结果就是这个二叉树已经平衡了
	void RotateRL(Node* parent) {
		Node* Rchild = parent->_right;
		Node* RLchild = Rchild->_left;
		int bf = RLchild->_bf;

		// 先右旋右子树
		RotateR(Rchild);
		// 再左旋父节点
		RotateL(parent);

		// 处理平衡因子
		// 如果右孩子的平衡因子==0说明右孩子是新插入的节点
		// 如果右孩子的平衡因子==1说明右孩子的左孩子是新插入的节点
		// 如果右孩子的平衡因子==-1说明右孩子的右孩子是新插入的节点

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

	// 删除节点，这个是根据find传入的返回值进行删除节点，不存在删除空树的问题
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
			balanceUpward(parent); // 删除后自下而上调整
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
			// 找到后继节点（右子树最左）
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

	// 向上平衡调整
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

	// 打印树结构（辅助函数，竖向显示）
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

	// 清空树（辅助函数，递归释放所有节点）
	void _clear(Node* node) {
		if (node == nullptr) return;
		_clear(node->_left);
		_clear(node->_right);
		delete node;
	}
};