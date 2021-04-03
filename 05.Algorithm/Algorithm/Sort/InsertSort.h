#ifndef _INSERT_SORT_
#define _INSERT_SORT_

template<typename T>
void InsertSort1(T arr[], int N){
	// ��0��Ԫ���Ѿ��������Դӵ�1��Ԫ�ؿ�ʼ
	for (int i = 1; i < N; i++){
		// ���ҵ�ǰԪ��arr[i]��[0,i)�еĺ���λ��
		for (int j = i; j>0; j--){
			// �����ǰλ��Ԫ�ر���֮ǰλ��Ԫ��С
			if (arr[j] < arr[j - 1]){
				swap(arr[j], arr[j - 1]);
			}
			else{// ��ǰλ��Ԫ�ر�֮ǰλ��Ԫ�ش��Ѿ�����
				break;
			}
		}
	}
}

//  ������㷨��swap������ķѴ���ʱ�䣬�����㷨ʱ�����ܲ�
//  �������Ż����㷨

template<typename T>
void InsertSort2(T arr[], int N){
	for (int i = 1; i < N; i++){
		T temp = arr[i];
		int j = 0; // ����Ԫ��tempӦ�ò����λ�� 
		for (j = i; j > 0 && arr[j - 1] > temp; j--){
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

#endif // _INSERT_SORT_