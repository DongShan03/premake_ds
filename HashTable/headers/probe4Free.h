

template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;//从起始桶出发
	while (ht[r])//沿查找链猪桶试探，直到首个空桶(无论是否带有懒惰删除标记)
	{
		r = (r + 1) % M;//为保证空桶总能找到，装填因子以及散列表长度需要合理设置
	}
	return r;
}