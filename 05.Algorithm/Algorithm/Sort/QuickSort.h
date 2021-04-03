#ifndef _QUICK_SORT_
#define _QUICK_SORT_

// ��arr[l...r]���ֽ���partition
// ����p��ʹ��arr[l...p-1] < arr[p]; arr[p+1...r] > arr[p]
template<typename T>
int __partition(T arr[], int l, int r){
	T v = arr[l];
	// arr[l+1, j] < v ; arr[j+1...i) > v
	int j = l;
	for (int i = l + 1; i <= r; i++){
		if (arr[i] < v){
			swap(arr[j + 1], arr[i]);
			j++;
		}
	}
	swap(arr[l], arr[j]);
	return j;
}

// ��arr[l...r]���ֽ��п�������
template<typename T>
void __quickSort(T arr[], int l, int r){
	if (l >= r){
		return;
	}
	int p = __partition(arr, l, r);
	__quickSort(arr, l, p - 1);
	__quickSort(arr, p + 1, r);
}

template<typename T>
void QuickSort(T arr[], int N){
	__quickSort(arr, 0, N - 1);
}

// ˫·���������㷨
template<typename T>
int __partition2(T arr[], int l, int r){
	// arr[l+1...i) <= v; arr(j...r] >= v
	T v = arr[l];
	int i = l + 1, j = r;
	while (1){
		while (i <= r && arr[i] < v){
			i++;
		}
		while (j >= l + 1 && arr[j] > v){
			j--;
		}
		if (i > j) break;
		swap(arr[i], arr[j]);
		i++;
		j--;
	}
	swap(arr[l], arr[j]);
	return j;
}

template<typename T>
void __quickSort2(T arr[], int l, int r){
	if (l >= r)return;
	int p = __partition2(arr, l, r);
	__quickSort2(arr, l, p - 1);
	__quickSort2(arr, p + 1, r);
}

template<typename T>
void QuickSort2(T arr[], int N){
	__quickSort2(arr, 0, N - 1);
}

// ��·���������㷨
// ��arr[l..r]��Ϊ <v ; ==v ; >v ������
// ֮��ݹ�� <v ; >v �����ּ���������·��������
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
	if (l >= r){
		return;
	}
	// partition
	T v = arr[l];
	int lt = l;     // arr[l+1...lt] < v
	int gt = r + 1; // arr[gt...r]   > v
	int i = l + 1;  // arr[lt+1...i) = v
	// arr[i]�ǵ�ǰ�����Ԫ��
	while (i < gt){
		if (arr[i] < v){
			swap(arr[i], arr[lt + 1]);
			lt++;
			i++;
		}
		else if (arr[i] > v){
			swap(arr[i], arr[gt - 1]);
			gt--;
		}
		else{
			i++;
		}
	}
	swap(arr[l], arr[lt]);
	__quickSort3Ways(arr, l, lt - 1);
	__quickSort3Ways(arr, gt, r);
}
template<typename T>
void QuickSort3Ways(T arr[], int N){
	__quickSort3Ways(arr, 0, N - 1);
}

#endif // _QUICK_SORT_
