#pragma once
#include<iostream>
using std::cin;
using std::cout;
// ����Ⱦȫ�������ռ�ͼ򻯴���֮��ȡ��ƽ��

// �Ȳ�����ģ�壬רע��int����


class Node
{
    friend class AVLTree;// ����ʹ������Ԫ������֤AVLTree����Է����ҵ�Node��˽�г�Ա
public:
    Node(int key)
        :_key(key), _left(nullptr), _right(nullptr),_height(1)
    {
    }

private:
    int _key;            // ��
    Node* _left;         // ������
    Node* _right;        // ������
    int _height;         // �ڵ�߶�
};

