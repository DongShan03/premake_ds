#include "bintree.h"


//һ���򵥵Ĳ�������
int main()
{
    BinTree<int>bt;
    //�����������Ϊ1
    BinNode<int>* root = bt.insertAsRoot(1);
    BinNode<int>* LeOfRoot = bt.insertAsLC(root, 2);
    BinNode<int>* RiOfRoot = bt.insertAsRC(root, 3);

    //���õڶ���ڵ�  ����Ϊ 4 5 6 7
    BinNode<int>* four, * five, * six, * seven;
    four = bt.insertAsLC(LeOfRoot, 4);
    five = bt.insertAsRC(LeOfRoot, 5);
    six = bt.insertAsLC(RiOfRoot, 6);
    seven = bt.insertAsRC(RiOfRoot, 7);

    //����������

    //�������
    bt.travPre(bt_visit<int>);
    cout << endl;

    //�������
    bt.travIn(bt_visit<int>);
    cout << endl;

    //�������
    bt.travPost(bt_visit<int>);
    cout << endl;

    //�������
    bt.travLevel(bt_visit<int>);
    cout << endl;

    //������ɾ���ڵ�
    bt.remove(seven);
    //�ٴα�������������ɾ��Ч��
    bt.travLevel(bt_visit<int>);
    cout << endl;

    //���ڵ�Ϊ3������ժ����Ȼ�����ԭ���Ķ������Լ��¶�����
    BinTree<int>* newTree = bt.secede(RiOfRoot);
    bt.travLevel(bt_visit<int>);
    cout << endl;
    newTree->travLevel(bt_visit<int>);
    cout << endl;


    //�������Ĺ�ģ
    cout << "size:" << bt.size() << endl;


    cout << "The test for BinaryTree is over!" << endl;
    return 0;

}
