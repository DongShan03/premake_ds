

template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
	{
		r = (r + 1) % M;//沿着查找链线性试探，跳过所有具有冲突的桶，以及带有懒惰删除标记的桶
	}
	return r;
}
