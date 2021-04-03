#ifndef _BUBBLE_SORT_
#define _BUBBLE_SORT_

/* 方法1：传统冒泡排序 */
#if 0
template<typename T>
void BubbleSort(T arr[], int N){
	for (int i = 0; i < N; i++){// 总共比较N-1趟
		for (int j = 1; j < N - i; j++){ // 每趟比较次数为 N-1-i
			if (arr[j - 1] > arr[j]){
				swap(arr[j - 1], arr[j]);
			}
		}
	}
}
#endif 

template<typename T>
void BubbleSort(T arr[], int N){
	for (int i = 0; i < N; i++){// 总共比较N-1趟
		// 标记某一趟比较是否发生了元素交换，如果没有发生，说明该趟已经有序，可以开始下一趟比较
		bool isSwaped = false;
		for (int j = 1; j < N - i; j++){ // 每趟比较次数为 N-1-i
			if (arr[j - 1] > arr[j]){
				swap(arr[j - 1], arr[j]);
				isSwaped = true;
			}
		}
		if (!isSwaped){
			break;
		}
	}
}

#endif // _BUBBLE_SORT_