#include "headers/hashtable.h"

using namespace std;
int main()
{
	HashTable<int, int>obj(100);
	obj.put(12, 12);
	if (obj.get(13))
	{
		cout << "founded!" << endl;
	}
	else
	{
		cout << "not founded!" << endl;
	}

	if (obj.get(12))
	{
		cout << "founded!" << endl;
	}
	else
	{
		cout << "not founded!" << endl;
	}
	obj.remove(12);


	if (obj.get(12))
	{
		cout << "founded!" << endl;
	}
	else
	{
		cout << "not founded!" << endl;
	}

	obj.put(100, 100);
	cout << obj.size() << endl;

	cout << "The test for HashTable is over!" << endl;
	return 0;
}
