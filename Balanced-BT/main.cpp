#define _CRT_SECURE_NO_WARNINGS
#include"AVLTree.hpp"


#include<vector>

#include <Windows.h>


// ��ʾ���˵�
void showMenu() {
    cout << "\n=== AVL�������˵� ===\n";
    cout << "1. ����ڵ�\n";
    cout << "2. ɾ���ڵ�\n";
    cout << "3. ���ҽڵ�\n";
    cout << "4. ��ӡ���ṹ\n";
    cout << "5. ��ӡ�������\n";
    cout << "6. ����Ĭ�ϲ���\n";
    cout << "7. �ϲ�����ƽ�������\n";
    cout << "0. �˳�\n";
    cout << "��ѡ�����: ";
}

// ����������
void handleInsert(AVLTree& tree) {
    cout << "������Ҫ���������ֵ: ";
    int key;
    cin >> key;
    tree.insert(key);
    cout << "������ɣ���ǰ���ṹ:\n";
    tree.printTree();
}

// ����ɾ������
void handleDelete(AVLTree& tree) {
    cout << "������Ҫɾ��������ֵ: ";
    int key;
    cin >> key;
    if (tree.remove(key)) {
        cout << "ɾ���ɹ�����ǰ���ṹ:\n";
    }
    else {
        cout << "δ�ҵ��ýڵ㣬��ǰ���ṹ:\n";
    }
    tree.printTree();
}

// ������Ҳ���
void handleSearch(AVLTree& tree) {
    cout << "������Ҫ���ҵ�����ֵ: ";
    int key;
    cin >> key;
    bool found = tree.findNode(key) != nullptr;
    cout << (found ? "�ҵ��ýڵ�\n" : "δ�ҵ��ýڵ�\n");
}

// ����Ĭ�ϲ���
void runDefaultTest(AVLTree& tree) {
    cout << "��������Ĭ�ϲ�������...\n";
    cout << "����˳��: ";
    std::vector<int> test{ 14, 9, 5, 17, 11, 12, 7, 19, 27, 8, 18, 23 };
    for (int val : test) {
        cout << val << " ";
        tree.insert(val);
        cout << endl << endl << endl << endl << endl;
        tree.printTree();
    }

    cout << "\n�������ṹ:\n";
    tree.printTree();
}

// �������ϲ�����
void handleMerge(AVLTree& tree) {
    AVLTree otherTree;
    cout << "�����������кϲ�...\n";
    cout << "������Ҫ��ӵ�����������ֵ(����-1��������):\n";

    std::vector<int> values;
    int value;
    while (true) {
        cout << "����ֵ(-1����): ";
        cin >> value;
        if (value == -1) break;
        values.push_back(value);
        otherTree.insert(value);
    }


    if (!values.empty()) {
        cout << "\n�½������ṹ:\n";
        otherTree.printTree();

        cout << "\n���ںϲ�������...\n";
        tree.merge(otherTree);

        cout << "�ϲ���ɣ���ǰ�����ṹ:\n";
        tree.printTree();
    }
    else {
        cout << "δ����κ�ֵ��ȡ���ϲ�����\n";
    }
}

void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}   

// �ָ�Ĭ�Ͽ���̨��ɫ
void resetConsoleColor()
{
    setConsoleColor(7);
}


void stop() { 
    char tem;
    scanf("%c", &tem);
    setConsoleColor(2);
    printf("������������� ");
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
            cout << "��ǰ���ṹ:\n";
            tree.printTree();
            break;
        case 5:
            cout << "����������: ";
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
            cout << "�������˳�����лʹ�ã�\n";
            break;
        default:
            cout << "��Чѡ�����������룡\n";
        }

  
        stop();
    } while (choice != 0);
	return 0;
}