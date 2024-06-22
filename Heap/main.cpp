
#include "heap.h"

int  main()
{
	Vector<int>obj;
	for (int i = 0; i < 100; i++)
	{
		obj.insert(i);
	}
	obj.unsort();
	obj.traverse(vector_visit);
	cout << endl;
	obj.heapSort(0, 100);
	obj.traverse(vector_visit);
	cout << "The test of heap is over!" << endl;
	return 0;
}
