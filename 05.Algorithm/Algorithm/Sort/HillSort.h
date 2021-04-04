#ifndef _HILL_SORT_
#define _HILL_SORT_

template<typename T>
void HillSort1(T arr[], int N){
	int gap = 1;
	while (gap< N / 3){
		gap = gap * 3 + 1;
	}
	for (gap; gap >= 1; gap /= 3){
		for (int i = gap; i < N; i++){
			// 查找当前元素arr[i]在[0,i)中的合适位置
			for (int j = i; j>=gap; j -= gap){
				// 如果当前位置元素比它之前位置元素小
				if (arr[j] < arr[j - gap]){
					swap(arr[j], arr[j - gap]);
				}
			}
		}
	}
}

template<typename T>
void HillSort2(T arr[], int N){
	int gap = 1;
	while (gap < N / 3){
		gap = gap * 3 + 1;
	}
	for (gap; gap >= 1; gap /= 3){
		for (int i = gap; i < N; i++){
			T temp = arr[i];
			int j = i;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

#endif // _HILL_SORT_