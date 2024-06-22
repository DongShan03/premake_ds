#include "avl.h"


int main()
{
    AVL<int>obj;

    for (int i = 0; i < 13; i++)
    {
        obj.insert(i);
    }

    cout << obj.root()->data << endl;

    if (!obj.search(5))
    {
        cout << "element 5 was not found!" << endl;
    }
    else
    {
        cout << "element 5 was found!" << endl;
    }

    obj.remove(1);

    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }

    if (!obj.search(1))
    {
        cout << "element 1 was not found!" << endl;
    }
    else
    {
        cout << "element 1 was found!" << endl;
    }


    obj.travIn(bt_visit<int>);
    cout << "The test of AVL is over!" << endl;
    return 0;
}
