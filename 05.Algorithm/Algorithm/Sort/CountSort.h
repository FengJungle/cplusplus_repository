#ifndef _COUNT_SORT_
#define _COUNT_SORT_

// ���ǻ��ڱȽϵ�����
// ʱ�临�Ӷȣ� O(n+k)����n��Ԫ�ع�ģ��k�Ƕ���ռ�
// �ȶ�����
void CountSort(int arr[], int n){
	// 1. �����ֵ����Сֵ
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

	// 2. ����ͳ�����飬ͳ�Ƹ���Ԫ�س��ִ���
	int* countArr = new int[max - min + 1];
	for (int i = 0; i < max - min + 1; i++){
		countArr[i] = 0;
	}
	for (int i = 0; i < n; i++){
		countArr[arr[i] - min]++;
	}

	// 3. ͳ��������Σ�ÿһ��Ԫ�ص�ֵ����֮ǰԪ�صĺ�
	for (int i = 1; i < max - min + 1; i++){
		countArr[i] += countArr[i - 1];
	}

	// 4. �������ԭʼ���У���ͳ���������ҵ���������λ��
	int *sortedArr = new int[n];
	for (int i = n - 1; i >= 0; i--){
		sortedArr[countArr[arr[i] - min] - 1] = arr[i];
		countArr[arr[i] - min]--;
	}

	// 5. ���Ƶ�ԭʼ����
	for (int i = 0; i < n; i++){
		arr[i] = sortedArr[i];
	}
	delete[] countArr;
	delete[] sortedArr;
}


#endif // _COUNT_SORT_