#pragma once
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

// ����Ⱦȫ�������ռ�ͼ򻯴���֮��ȡ��ƽ��

// �Ȳ�����ģ�壬רע��int����


class Node
{
    friend class AVLTree;// ����ʹ������Ԫ������֤AVLTree����Է����ҵ�Node��˽�г�Ա
public:
    Node(int key)
        :_key(key), _left(nullptr), _right(nullptr), _bf(0),_parent(nullptr)
    {
    }

private:
    int _key;            // ��
    Node* _left;         // ������
    Node* _right;        // ������
    Node* _parent;       // ���ڵ�
    int _bf;             // ƽ������
};

