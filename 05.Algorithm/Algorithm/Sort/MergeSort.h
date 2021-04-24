#ifndef _MERGE_SORT_
#define _MERGE_SORT_

template<typename T>
void __merge(T arr[], int l, int mid, int r){
	T *aux = new T[r - l + 1];
	for (int i = l; i <= r; i++){
		aux[i - l] = arr[i];
	}

	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++){
		if (i > mid){
			arr[k] = aux[j - l];
			j++;
		}
		else if (j > r){
			arr[k] = aux[i - l];
			i++;
		}
		else if (aux[i - l] < aux[j - l]){
			arr[k] = aux[i - l];
			i++;
		}
		else{
			arr[k] = aux[j - l];
			j++;
		}
	}
	delete[] aux;
}

template<typename T>
void __mergeSort(T arr[], int l, int r){
	if (l >= r){
		return;
	}

	int mid = (l + r) / 2;
	__mergeSort(arr, l, mid);
	__mergeSort(arr, mid + 1, r);
	if (arr[mid] > arr[mid + 1]){
		__merge(arr, l, mid, r);
	}
}

template<typename T>
void MergeSort(T arr[], int N){
	__mergeSort(arr, 0, N - 1);
}

// 自底向上归并排序
void mergeSortBU(int arr[], int N)
{
	for (int sz = 1; sz < N; sz += sz)
	{
		for (int i = 0; i + sz < N; i += 2 * sz)
		{
			__merge(arr, i, i + sz - 1, min(i + 2 * sz - 1, N - 1));
		}
	}
}

#endif // _MERGE_SORT_