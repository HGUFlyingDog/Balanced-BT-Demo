#include"AVLTree.hpp"

#include<vector>
// 显示主菜单
void showMenu() {
    cout << "\n=== AVL树操作菜单 ===\n";
    cout << "1. 插入节点\n";
    cout << "2. 删除节点\n";
    cout << "3. 查找节点\n";
    cout << "4. 打印树结构\n";
    cout << "5. 运行默认测试\n";
    cout << "0. 退出\n";
    cout << "请选择操作: ";
}

// 处理插入操作
void handleInsert(AVLTree& tree) {
    cout << "请输入要插入的整数值: ";
    int key;
    std::cin >> key;
    tree.insert(key);
    cout << "插入完成，当前树结构:\n";
    tree.printTree();
}

// 处理删除操作
void handleDelete(AVLTree& tree) {
    cout << "请输入要删除的整数值: ";
    int key;
    std::cin >> key;
    if (tree.remove(key)) {
        cout << "删除成功，当前树结构:\n";
    }
    else {
        cout << "未找到该节点，当前树结构:\n";
    }
    tree.printTree();
}

// 处理查找操作
void handleSearch(AVLTree& tree) {
    cout << "请输入要查找的整数值: ";
    int key;
    std::cin >> key;
    bool found = tree.findNode(key) != nullptr;
    cout << (found ? "找到该节点\n" : "未找到该节点\n");
}

// 运行默认测试
void runDefaultTest(AVLTree& tree) {
    cout << "正在运行默认测试用例...\n";
    cout << "插入顺序: ";
    std::vector<int> test{ 14,9,5,17,11,12,7,19,27,8,18,23 };
    for (int val : test) {
        cout << val << " ";
        tree.insert(val);
    }

    cout << "\n最终树结构:\n";
    tree.printTree();
}


int main()
{
	AVLTree tree;

	std::vector<int> test{ 14,9,5,17,11,12,7,19,27,8,18,23 };

	for (auto ch:test)
	{
    		tree.insert(ch);
	}

	tree.printTree();
	
	tree.remove(5);

	cout << endl << endl << endl << endl << endl << endl << endl;
	tree.printTree();


    /*AVLTree tree;
    int choice = -1;

    while (choice != 0) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: handleInsert(tree); break;
        case 2: handleDelete(tree); break;
        case 3: handleSearch(tree); break;
        case 4: tree.printTree(); break;
        case 5: runDefaultTest(tree); break;
        case 0: cout << "程序已退出\n"; break;
        default: cout << "无效选择，请重新输入！\n";
        }
    }*/
	return 0;
}