#include "rbtree.h"

int main()
{
    RedBlack<int>obj;

    for (int i = 0; i < 20; i++)
    {
        obj.insert(i);
    }
    

    for (int i = 15; i < 20; i++)
    {
        cout << "time to remove " << i << endl;
        obj.remove(i);
        rbtravIn(obj.root(), rbt_visit<int>);
        cout << endl;
        rbtravPre(obj.root(), rbt_visit<int>);
        cout << endl;
    }
    cout << "The test of rbtree is over!" << endl;
    return 0;
}