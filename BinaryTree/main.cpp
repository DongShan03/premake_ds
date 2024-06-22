#include "bintree.h"


//一个简单的测试用例
int main()
{
    BinTree<int>bt;
    //将根结点设置为1
    BinNode<int>* root = bt.insertAsRoot(1);
    BinNode<int>* LeOfRoot = bt.insertAsLC(root, 2);
    BinNode<int>* RiOfRoot = bt.insertAsRC(root, 3);

    //设置第二层节点  假设为 4 5 6 7
    BinNode<int>* four, * five, * six, * seven;
    four = bt.insertAsLC(LeOfRoot, 4);
    five = bt.insertAsRC(LeOfRoot, 5);
    six = bt.insertAsLC(RiOfRoot, 6);
    seven = bt.insertAsRC(RiOfRoot, 7);

    //遍历二叉树

    //先序遍历
    bt.travPre(bt_visit<int>);
    cout << endl;

    //中序遍历
    bt.travIn(bt_visit<int>);
    cout << endl;

    //后序遍历
    bt.travPost(bt_visit<int>);
    cout << endl;

    //层序遍历
    bt.travLevel(bt_visit<int>);
    cout << endl;

    //二叉树删除节点
    bt.remove(seven);
    //再次遍历二叉树测试删除效果
    bt.travLevel(bt_visit<int>);
    cout << endl;

    //将节点为3的子树摘除，然后遍历原来的二叉树以及新二叉树
    BinTree<int>* newTree = bt.secede(RiOfRoot);
    bt.travLevel(bt_visit<int>);
    cout << endl;
    newTree->travLevel(bt_visit<int>);
    cout << endl;


    //返回树的规模
    cout << "size:" << bt.size() << endl;


    cout << "The test for BinaryTree is over!" << endl;
    return 0;

}
