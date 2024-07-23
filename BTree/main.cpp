#include "headers/btree.h"


int main()
{
    BTree<int>obj;
    for (int i = 0; i < 100; i++)
    {
        obj.insert(i);
    }
    cout << obj.empty() << endl;
    cout << ((obj.search(1) != NULL) ? "founded" : "not founded!") << endl;
    obj.remove(1);
    cout << ((obj.search(1) != NULL) ? "founded" : "not founded!") << endl;
    cout << ((obj.search(80) != NULL) ? "founded" : "not founded!") << endl;
    cout << "The test of BTree is over!" << endl;
    return 0;
}
