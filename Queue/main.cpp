#include "queue.h"


int main()
{
	Queue<int>que;
	for (int i = 0; i < 100; i++)
	{
		que.enqueue(i);
	}

	int i = 0;
	while (!que.empty())
	{
		cout << que.front() << "  ";
		i++;
		if (i % 10 == 0)
		{
			cout << endl;
		}
		que.dequeue();
	}
	cout << "The test for queue is over!" << endl;
	return 0;
}
