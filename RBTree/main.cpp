#include "rbtree.h"

int main()
{
    RedBlack<int>obj;

    for (int i = 0; i < 125; i++)
    {
        obj.insert(i);
    }
    obj.travIn(bt_visit<int>);
    for (int i = 10; i < 118; i++)
    {
        cout << "time to remove " << i << endl;
        obj.remove(i);
    }

    
    cout << "The test of rbtree is over!" << endl;
    return 0;
}