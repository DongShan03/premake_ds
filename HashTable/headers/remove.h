
template<typename K, typename V>
bool HashTable<K, V>::remove(K k)
{
	//散列表词条删除算法
	int r = probe4Hit(k);
	if (!ht[r])
	{
		return false;//对应词条不存在的时候，无法删除
	}
	release(ht[r]);
	ht[r] = NULL;
	markAsRemoved(r);
	N--;
	return true;//否则释放桶中的词条，设置懒惰删除标记，并更新词条总数
}
