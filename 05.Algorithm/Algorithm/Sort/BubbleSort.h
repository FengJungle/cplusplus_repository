#ifndef _BUBBLE_SORT_
#define _BUBBLE_SORT_

/* ����1����ͳð������ */
#if 0
template<typename T>
void BubbleSort(T arr[], int N){
	for (int i = 0; i < N; i++){// �ܹ��Ƚ�N-1��
		for (int j = 1; j < N - i; j++){ // ÿ�˱Ƚϴ���Ϊ N-1-i
			if (arr[j - 1] > arr[j]){
				swap(arr[j - 1], arr[j]);
			}
		}
	}
}
#endif 

template<typename T>
void BubbleSort(T arr[], int N){
	for (int i = 0; i < N; i++){// �ܹ��Ƚ�N-1��
		// ���ĳһ�˱Ƚ��Ƿ�����Ԫ�ؽ��������û�з�����˵�������Ѿ����򣬿��Կ�ʼ��һ�˱Ƚ�
		bool isSwaped = false;
		for (int j = 1; j < N - i; j++){ // ÿ�˱Ƚϴ���Ϊ N-1-i
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