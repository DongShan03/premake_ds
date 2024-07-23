#include "headers/vector.h"

int main()
{
    Vector<int>obj;
    //生成随机数*100，插入向量中
    srand((unsigned)time(NULL));
    for (int i = 0; i < 20; i++)
    {
        obj.insert(rand() % 1000);
    }

    cout << "------------------01.Initial vector:-----------------" << endl;
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------02.Insert a value:-----------------" << endl;
    obj.insert(1);
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------03.After sorted:-------------------" << endl;
    obj.sort();
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------04.After deduplicated:---------------" << endl;
    obj.deduplicate();
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------05.After shuffled:----------------" << endl;
    obj.unsort();
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------06.After uniquify:----------------" << endl;
    obj.insert(1, 2);
    obj.uniquify();
    obj.traverse(vector_visit);
    cout << endl;

    cout << "------------------07.Search a element 100 one by one:----------------" << endl;
    int res = obj.find(100);
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------08.Search a element 19 by fib search01:----------------" << endl;
    //define an array with 20 elements
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = fibSearchA(a, 19, 0, sizeof(a) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    cout << "------------------09.Search a element 19 by fib search02:----------------" << endl;
    //define an array with 20 elements
    int b[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = fibSearchB(b, 19, 0, sizeof(b) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------10.Search a element 19 by binary search01:----------------" << endl;
    //define an array with 20 elements
    int c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchA(b, 19, 0, sizeof(c) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    cout << "------------------11.Search a element 19 by binary search02:----------------" << endl;
    //define an array with 20 elements
    int d[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchB(d, 19, 0, sizeof(d) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;

    cout << "------------------12.Search a element 19 by binary search03:----------------" << endl;
    //define an array with 20 elements
    int e[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    res = binSearchC(e, 19, 0, sizeof(e) / sizeof(int));
    cout << (res == -1 ? "not found!" : "founded") << endl;
    cout << endl;


    cout << "The test for Vector is over!" << endl;
    return 0;
}
