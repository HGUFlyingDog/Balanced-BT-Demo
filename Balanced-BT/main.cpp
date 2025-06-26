#include"AVLTree.hpp"

#include<vector>
// ��ʾ���˵�
void showMenu() {
    cout << "\n=== AVL�������˵� ===\n";
    cout << "1. ����ڵ�\n";
    cout << "2. ɾ���ڵ�\n";
    cout << "3. ���ҽڵ�\n";
    cout << "4. ��ӡ���ṹ\n";
    cout << "5. ����Ĭ�ϲ���\n";
    cout << "0. �˳�\n";
    cout << "��ѡ�����: ";
}

// ����������
void handleInsert(AVLTree& tree) {
    cout << "������Ҫ���������ֵ: ";
    int key;
    std::cin >> key;
    tree.insert(key);
    cout << "������ɣ���ǰ���ṹ:\n";
    tree.printTree();
}

// ����ɾ������
void handleDelete(AVLTree& tree) {
    cout << "������Ҫɾ��������ֵ: ";
    int key;
    std::cin >> key;
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
    std::cin >> key;
    bool found = tree.findNode(key) != nullptr;
    cout << (found ? "�ҵ��ýڵ�\n" : "δ�ҵ��ýڵ�\n");
}

// ����Ĭ�ϲ���
void runDefaultTest(AVLTree& tree) {
    cout << "��������Ĭ�ϲ�������...\n";
    cout << "����˳��: ";
    std::vector<int> test{ 14,9,5,17,11,12,7,19,27,8,18,23 };
    for (int val : test) {
        cout << val << " ";
        tree.insert(val);
    }

    cout << "\n�������ṹ:\n";
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
        case 0: cout << "�������˳�\n"; break;
        default: cout << "��Чѡ�����������룡\n";
        }
    }*/
	return 0;
}