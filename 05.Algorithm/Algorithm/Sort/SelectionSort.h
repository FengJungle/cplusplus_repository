#ifndef _SELECTION_SORT_H
#define _SELECTION_SORT_H

#include <algorithm>

template<typename T>
void SelectionSort(T arr[], int N){
	for (int i = 0; i < N; i++){
		int minIndex = i;
		// Find minValue between [i, n) and save its index to minIndex
		for (int j = i + 1; j < N; j++){
			if (arr[j] < arr[minIndex]){
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
	}
}

#endif // _SELECTION_SORT_H