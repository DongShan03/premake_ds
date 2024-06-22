#include "rbtree.h"

using namespace std;


int main()
{
    RedBlack<int>obj;

    for (int i = 0; i < 15; i++)
    {
        obj.insert(i);
    }
    
    if (!obj.search(5))
    {
        cout << "element 5 was not found!" << endl;
    }
    else
    {
        cout << "element 5 was found!" << endl;
    }
    obj.remove(5);

    if (obj.empty())
    {
        cout << "Tree is empty" << endl;
    }

    if (!obj.search(5))
    {
        cout << "element 5 was not found!" << endl;
    }
    else
    {
        cout << "element 5 was found!" << endl;
    }

    // obj.travIn(bt_visit<int>);
    cout << "The test of rbtree is over!" << endl;
    return 0;
}
