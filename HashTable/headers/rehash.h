

template<typename K, typename V>
void HashTable<K, V>::rehash()
{
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576);
	N = 0;
	ht = new Entry<K, V> * [M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);
	for (int i = 0; i < old_capacity; i++)
	{
		if (old_ht[i])
		{
			put(old_ht[i]->key, old_ht[i]->value);
		}
	}
	release(old_ht);
}
