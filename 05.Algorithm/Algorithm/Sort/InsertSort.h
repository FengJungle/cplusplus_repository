#ifndef _INSERT_SORT_
#define _INSERT_SORT_

template<typename T>
void InsertSort1(T arr[], int N){
	// 第0个元素已经有序，所以从第1个元素开始
	for (int i = 1; i < N; i++){
		// 查找当前元素arr[i]在[0,i)中的合适位置
		for (int j = i; j>0; j--){
			// 如果当前位置元素比它之前位置元素小
			if (arr[j] < arr[j - 1]){
				swap(arr[j], arr[j - 1]);
			}
			else{// 当前位置元素比之前位置元素大，已经有序
				break;
			}
		}
	}
}

//  上面的算法，swap操作会耗费大量时间，导致算法时间性能差
//  下面是优化的算法

template<typename T>
void InsertSort2(T arr[], int N){
	for (int i = 1; i < N; i++){
		T temp = arr[i];
		int j = 0; // 保存元素temp应该插入的位置 
		for (j = i; j > 0 && arr[j - 1] > temp; j--){
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

#endif // _INSERT_SORT_