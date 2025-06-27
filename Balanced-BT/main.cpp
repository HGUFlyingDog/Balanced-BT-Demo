#define _CRT_SECURE_NO_WARNINGS
#include"AVLTree.hpp"


#include<vector>

#include <Windows.h>


// 显示主菜单
void showMenu() {
    cout << "\n=== AVL树操作菜单 ===\n";
    cout << "1. 插入节点\n";
    cout << "2. 删除节点\n";
    cout << "3. 查找节点\n";
    cout << "4. 打印树结构\n";
    cout << "5. 打印中序遍历\n";
    cout << "6. 运行默认测试\n";
    cout << "7. 合并两棵平衡二叉树\n";
    cout << "0. 退出\n";
    cout << "请选择操作: ";
}

// 处理插入操作
void handleInsert(AVLTree& tree) {
    cout << "请输入要插入的整数值: ";
    int key;
    cin >> key;
    tree.insert(key);
    cout << "插入完成，当前树结构:\n";
    tree.printTree();
}

// 处理删除操作
void handleDelete(AVLTree& tree) {
    cout << "请输入要删除的整数值: ";
    int key;
    cin >> key;
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
    cin >> key;
    bool found = tree.findNode(key) != nullptr;
    cout << (found ? "找到该节点\n" : "未找到该节点\n");
}

// 运行默认测试
void runDefaultTest(AVLTree& tree) {
    cout << "正在运行默认测试用例...\n";
    cout << "插入顺序: ";
    std::vector<int> test{ 14, 9, 5, 17, 11, 12, 7, 19, 27, 8, 18, 23 };
    for (int val : test) {
        cout << val << " ";
        tree.insert(val);
        cout << endl << endl << endl << endl << endl;
        tree.printTree();
    }

    cout << "\n最终树结构:\n";
    tree.printTree();
}

// 处理树合并操作
void handleMerge(AVLTree& tree) {
    AVLTree otherTree;
    cout << "创建新树进行合并...\n";
    cout << "请输入要添加到新树的整数值(输入-1结束输入):\n";

    std::vector<int> values;
    int value;
    while (true) {
        cout << "输入值(-1结束): ";
        cin >> value;
        if (value == -1) break;
        values.push_back(value);
        otherTree.insert(value);
    }


    if (!values.empty()) {
        cout << "\n新建的树结构:\n";
        otherTree.printTree();

        cout << "\n正在合并到主树...\n";
        tree.merge(otherTree);

        cout << "合并完成，当前主树结构:\n";
        tree.printTree();
    }
    else {
        cout << "未添加任何值，取消合并操作\n";
    }
}

void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}   

// 恢复默认控制台颜色
void resetConsoleColor()
{
    setConsoleColor(7);
}


void stop() { 
    char tem;
    scanf("%c", &tem);
    setConsoleColor(2);
    printf("按下任意键继续 ");
    resetConsoleColor();
    scanf("%c", &tem);
    system("cls");
}

int main()
{
	//AVLTree tree;

	//std::vector<int> test{ 14,9,5,17,11,12,7,19,27,8,18,23 };

	//for (auto ch:test)
	//{
 //   		tree.insert(ch);
	//}

 //   cout << endl << endl << endl << endl << endl << endl << endl;

	//tree.printTree();
	//
	//tree.remove(5);

	//cout << endl << endl << endl << endl << endl << endl << endl;
	//tree.printTree();


    AVLTree tree;
    int choice = 0;



    do {
        showMenu();
        cin >> choice;

  

        switch (choice) {
        case 1:
            handleInsert(tree);
            break;
        case 2:
            handleDelete(tree);
            break;
        case 3:
            handleSearch(tree);
            break;
        case 4:
            cout << "当前树结构:\n";
            tree.printTree();
            break;
        case 5:
            cout << "中序遍历结果: ";
            tree.print();
            cout << endl;
            break;
        case 6:
            runDefaultTest(tree);
            break;
        case 7:
            handleMerge(tree);
            break;
        case 0:
            cout << "程序已退出，感谢使用！\n";
            break;
        default:
            cout << "无效选择，请重新输入！\n";
        }

  
        stop();
    } while (choice != 0);
	return 0;
}