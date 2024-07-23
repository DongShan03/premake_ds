#include "headers/bitmap.h"

int main()
{
	int n = 1000;
	Bitmap bt(n);
	for (int i = 0; i < n; i++)
	{
		bt.set(i);
	}
	if (bt.test(80))
	{
		cout << "founded!" << endl;
	}
	else
	{
		cout << "not founded!" << endl;
	}
	cout << "The test for Bitmap is over!" << endl;
	return 0;
}
