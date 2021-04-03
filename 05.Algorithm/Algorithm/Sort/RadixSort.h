#ifndef _RADIX_SORT_
#define _RADIX_SORT_

int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
	int maxData = data[0];        
	// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i)
	{
		if (maxData < data[i]){
			maxData = data[i];
		}
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;
}
// 基数排序
void RadixSort(int data[], int n) 
{
	int d = maxbit(data, n);
	int *tmp = new int[n];
	// 计数器
	int *count = new int[10]; 
	int i, j, k;
	int radix = 1;
	// 进行d次排序
	for (i = 1; i <= d; i++) 
	{
		// 每次分配前清空计数器
		for (j = 0; j < 10; j++){
			count[j] = 0; 
		}
		// 统计每个桶中的记录数
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; 
			count[k]++;
		}
		// 将tmp中的位置依次分配给每个桶
		for (j = 1; j < 10; j++){
			count[j] = count[j - 1] + count[j];
		}
		// 将所有桶中记录依次收集到tmp中
		for (j = n - 1; j >= 0; j--) 
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		// 将临时数组的内容复制到data中
		for (j = 0; j < n; j++) {
			data[j] = tmp[j];
		}
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}

#endif // _RADIX_SORT_