#ifndef _COUNT_SORT_
#define _COUNT_SORT_

// 不是基于比较的排序
// 时间复杂度： O(n+k)——n是元素规模，k是额外空间
// 稳定排序
void CountSort(int arr[], int n){
	// 1. 找最大值和最小值
	int max = arr[0];
	int min = arr[0];
	for (int i = 1; i < n; i++){
		if (arr[i]>max){
			max = arr[i];
		}
		if (arr[i] < min){
			min = arr[i];
		}
	}

	// 2. 创建统计数组，统计各个元素出现次数
	int* countArr = new int[max - min + 1];
	for (int i = 0; i < max - min + 1; i++){
		countArr[i] = 0;
	}
	for (int i = 0; i < n; i++){
		countArr[arr[i] - min]++;
	}

	// 3. 统计数组变形，每一个元素的值等于之前元素的和
	for (int i = 1; i < max - min + 1; i++){
		countArr[i] += countArr[i - 1];
	}

	// 4. 倒序遍历原始序列，从统计数组中找到最终排序位置
	int *sortedArr = new int[n];
	for (int i = n - 1; i >= 0; i--){
		sortedArr[countArr[arr[i] - min] - 1] = arr[i];
		countArr[arr[i] - min]--;
	}

	// 5. 复制到原始数组
	for (int i = 0; i < n; i++){
		arr[i] = sortedArr[i];
	}
	delete[] countArr;
	delete[] sortedArr;
}


#endif // _COUNT_SORT_