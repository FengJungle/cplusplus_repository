#ifndef _HEAP_SORT_
#define _HEAP_SORT_

#include "Heap.h"

// 结论：
// 将n个元素逐个插入到一个空堆中，算法复杂度是O(nlogn)
template<typename T>
void HeapSort1(T arr[], int N){
	MaxHeap<T> maxheap = MaxHeap<T>(N);
	for (int i = 0; i < N; i++){
		maxheap.insert(arr[i]);
	}
	// 从小到大排序
	for (int i = N - 1; i >= 0; i--){
		arr[i] = maxheap.getMax();
	}
}

// 结论：
// heapify,算法复杂度是O(n)
template<typename T>
void HeapSort2(T arr[], int N){
	MaxHeap<T> maxheap = MaxHeap<T>(arr, N);
	for (int i = N - 1; i >= 0; i--){
		arr[i] = maxheap.getMax();
	}
}

// 原地堆排序 : 不需要额外的空间
template<typename T>
void __shiftDown(T arr[], int n, int k){
	while (2 * k + 1 < n){
		int j = 2 * k + 1;
		if (j+1 < n && arr[j] < arr[j + 1]){
			j = j + 1;
		}
		if (arr[k] >= arr[j]){
			break;
		}
		swap(arr[k], arr[j]);
		k = j;
	}
}
template<typename T>
void HeapSort3(T arr[], int N){
	for (int i = (N - 1 - 1) / 2; i >= 0; i--){
		__shiftDown(arr, N, i);
	}
	for (int i = N - 1; i > 0; i--){
		swap(arr[0], arr[i]);
		__shiftDown(arr, i, 0);
	}
}


#endif // _HEAP_SORT_