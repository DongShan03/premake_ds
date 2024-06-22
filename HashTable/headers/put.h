
template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v)
{
	//散列表词条插入
	if (ht[probe4Hit(k)])
	{
		return false;//雷同元素不必重复插入
	}
	int r = probe4Free(k);//为词条找到一个空桶
	ht[r] = new Entry<K, V>(k, v);
	N++;//插入，注意懒惰删除标记无需复位
	if (N * 2 > M)
	{
		rehash();//装填因子高于50%之后重散列
	}
	return true;
}