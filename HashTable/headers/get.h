template<typename K, typename V>
V* HashTable<K, V>::get(K k)
{
	//散列词条查找算法
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r]->value) : NULL;//禁止词条key值雷同
}
