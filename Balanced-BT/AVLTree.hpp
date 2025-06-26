#pragma once
#include<iostream>
#include"Node.hpp"

class AVLTree
{
public:
	AVLTree() {};
	
	~AVLTree() {};


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
		cout << "现在插入的节点是：" << key << endl;
		if (_root == nullptr)//适用于创建节点时候的初始化部分，如果是空的节点就动态开辟一个
		{
			_root = new Node(key);
			return;
		}
		// 这里使用一个cur表示当前节点和一个prev表示当前节点的前一个节点方便进行链表的插入
		// 但是后来随着我对代码理解的深入，我在Node里面增加了一个parent来表示prev，后期把这个代码优化一下变得更加简洁
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
			else// 我的二叉搜索树目前不支持相同关键字的插入，虽然非法插入，但是不至于抛异常
			{
				cout << "插入" << key << "失败，因为有重复的节点" << endl;
				return;
			}
		}

		cur = new Node(key);// 这里就是找到了插入的部分，新建节点然后开始插入，调用的是Node的构造函数
		if (key < prev->_key)
		{
			prev->_left = cur;
		}
		if (key > prev->_key)
		{
			prev->_right = cur;
		}

		cur->_parent = prev;
		this->print();//测试一下插入的结果

		// 控制平衡
		// 更新平衡因子
		// 最坏情况下更新到根节点
		while (prev)
		{
			//这个判断条件的目的就是
			// 1. 在左子树插入，parent平衡因子++
			// 2. 在右子树插入，parent平衡因子--

			if (cur == prev->_left)
			{
				prev->_bf++;
			}
			else
			{
				prev->_bf--;
			}

			if (prev->_bf == 0)  return;//更新结束 节点已经平衡，不会再往上影响父节点了
			if (abs(prev->_bf) == 1)
			{
				//继续向上更新
				cur = prev;
				prev = prev->_parent;

			}
			//else if (abs(prev->_bf) == 2)
			//{
			//	// 子树出现问题需要旋转
			//	// 左旋 RR 对应的 特点是失衡节点的平衡因子是-2，失衡节点的右孩子的平衡因子是-1
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
				// 根据实际子节点判断旋转类型
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
				break; // 旋转后退出循环
			}
			else//平衡因子不等于上面出现的五个数字，直接抛异常，我的程序有大的bug
			{
				throw"平衡因子出现问题";
			}
		}
	}

	// 删除节点并维护平衡
	

private:
	Node* _root = nullptr; // 根节点指针


	// 这个就是左旋的操作,要求传入一个Node*的节点实施旋转功能，结果就是部分的结构被旋转了
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

		else
		{
			_root = cur; // 更新根节点
			cur->_parent = nullptr;
		}

		cur->_bf = parent->_bf = 0;
	}


	//这个就是右旋的操作，跟左旋差不多，就是顺序换一下，要求传入一个Node*的节点实施旋转功能，结果就是部分的结构被旋转了
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
			_root = cur; // 更新根节点
			cur->_parent = nullptr;
		}
		cur->_bf = parent->_bf = 0;
	}

	// 操作就是对右旋右孩子然后左旋，要求传入一个Node*的节点实施旋转功能，结果就是这个二叉树已经平衡了
	void RotateRL(Node* parent)
	{
		Node* Rchild = parent->_right;
		Node* RLchild = Rchild->_left;

		// 先对右孩子右旋
		RotateR(Rchild);
		// 再对parent左旋
		RotateL(parent);

		// 旋转后平衡因子的调整
		// RLchild 旋转前的 _bf 决定了 parent 和 Rchild 的新 _bf
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

	// 操作就是对左旋左孩子然后右旋，要求传入一个Node*的节点实施旋转功能，结果就是这个二叉树已经平衡
	void RotateLR(Node* parent)
	{
		Node* Lchild = parent->_left;
		Node* LRchild = Lchild->_right;

		// 先对左孩子左旋
		RotateL(Lchild);
		// 再对parent右旋
		RotateR(parent);

		// 旋转后平衡因子的调整
		// 根据LRchild的_bf调整parent和Lchild的_bf
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