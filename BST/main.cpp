#include "headers/bst.h"

int main()
{
    BST<int>obj;
    for (int i = 0; i < 15; i++)
    {
        obj.insert(i);
    }
    obj.travIn(bt_visit<int>);
    cout << endl;
    if (!obj.search(5))
    {
        cout << "element 5 not found!" << endl;
    }
    obj.remove(1);
    obj.travIn(bt_visit<int>);
    cout << endl;
    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }
    cout << "The test of BST is over!" << endl;
    return 0;
}
