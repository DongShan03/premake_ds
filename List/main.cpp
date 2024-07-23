#include "headers/list.h"

int main()
{
    List<int>obj;


    cout << "------------------01.Initial list:-----------------" << endl;
    //生成随机数*20，插入向量中
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        //使用头插法与尾插法
        obj.insertAsFirst(rand() % 1000);
        obj.insertAsLast(rand() % 2000);
    }
    cout << "Insert successed!" << endl;
    cout << endl;

    cout << "------------------02.Traverse list:-----------------" << endl;
    obj.traverse(list_visit);
    cout << endl;

    cout << "------------------03.Insert  values at head:-----------------" << endl;
    obj.insertAsFirst(1);
    obj.traverse(list_visit);
    cout << endl;

    cout << "------------------04.Insert  values at end:-----------------" << endl;
    obj.insertAsLast(2);
    obj.traverse(list_visit);
    cout << endl;

    cout << "------------------05.find a element with a concret value:-----------------" << endl;
    ListNode<int>* aNode = obj.find(1);
    if (aNode != NULL)
    {
        cout << "An element with a value 1 was founded!" << endl;
    }
    else
    {
        cout << "An element with a value 1 was not founded!" << endl;
    }
    cout << endl;

    cout << "------------------06.report the size of this list:-----------------" << endl;
    int x = obj.size();
    cout << "the size of this list is:" << x << endl;
    cout << endl;


    cout << "------------------07.get the position of head of this list:-----------------" << endl;
    ListNode<int>* h = obj.first();
    cout << "the address of the first node of this list on my computer is:" << h << endl;
    cout << endl;


    cout << "------------------08.get the position of tail of this list:-----------------" << endl;
    ListNode<int>* t = obj.last();
    cout << "the address of the last node of this list on my computer is:" << t << endl;
    cout << endl;


    cout << "------------------09.test insert a node at left of aother node:-----------------" << endl;
    obj.insertA(t, 250);
    obj.traverse(list_visit);
    cout << endl;

    cout << "------------------10.test insert a node at right of aother node:-----------------" << endl;
    obj.insertB(t, 250);
    obj.traverse(list_visit);//值得注意的是，此时的t并未被修改
    cout << endl;


    cout << "------------------11.remove a node:-----------------" << endl;
    obj.remove(t);
    obj.traverse(list_visit);
    cout << endl;

    //cout << "------------------12.judge all nodes were sorted in descending order:-----------------" << endl;
    //bool res=obj.disordered();
    //cout << res << endl;
    //cout << endl;

    cout << "------------------13.sort list:-----------------" << endl;
    obj.sort();
    obj.traverse(list_visit);
    cout << endl;

    cout << "------------------14.search a node in this list:-----------------" << endl;
    ListNode<int>* res = obj.search(20);
    cout << "the result of searching:" << (res->data == 20 ? "success" : "failed") << endl;
    cout << endl;

    cout << "------------------15.uniquify this list:-----------------" << endl;
    obj.uniquify();
    obj.traverse(list_visit);
    cout << endl;


    cout << "------------------16.dedupliacate this list:-----------------" << endl;
    obj.insertAsFirst(10);
    obj.insertAsFirst(10);
    obj.insertAsFirst(10);
    cout << endl;
    cout << "before deduplicated:" << endl;
    obj.traverse(list_visit);
    obj.deduplicate();
    cout << endl;
    cout << "after deduplicated:" << endl;
    obj.traverse(list_visit);
    cout << endl;

    cout << "The test for list is over!" << endl;
    return 0;
}

