#ifndef _MERGE_SORT_
#define _MERGE_SORT_

// �鲢���򣺶���ʹ��O(n)�Ŀռ䣬 ʱ�临�Ӷ�O(nlogn)

// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
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

// �ݹ�ʹ�ù鲢���򣬶�arr[l...r]�ķ�Χ��������
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

// �Ե����ϵĹ鲢�����㷨
//template<typename T>
//void mergeSortBU(T arr[], int N){
//	for (int sz = 1; sz <= N; sz *= 2){
//		for (int i = 0; i + sz < N; i += sz + sz){
//			// ��arr[i....i+sz-1]��arr[i+sz...i+2*sz-1]���й鲢
//			__merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1);
//		}
//	}
//}

#endif // _MERGE_SORT_