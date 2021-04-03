#ifndef _BINARYSEARCH_
#define _BINARYSEARCH_

// ���ֲ��ҷ�������������arr�У�����target
// ����ҵ�target������target��arr�е�����
// ���û���ҵ����򷵻�-1
template<typename T>
int binarySearch(T arr[], int n, T target){
	// ��arr[l...r]����target
	int l = 0, r = n - 1;
	while (l <= r){
		//int mid = (l + r) / 2;
		int mid = l + (r - l) / 2;
		if (arr[mid] == target){
			return mid;
		}
		if (target < arr[mid]){
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	return -1;
}

// �õݹ�ķ�ʽд���ֲ��ҷ�
template<typename T>
int __binarySearch2(T arr[], int l, int r, T target){
	if (l > r)
		return -1;

	//int mid = (l+r)/2;
	// ��ֹ��������µ����������ʹ��������߼����mid
	int mid = l + (r - l) / 2;

	if (arr[mid] == target)
		return mid;
	else if (arr[mid] > target)
		return __binarySearch2(arr, l, mid - 1, target);
	else
		return __binarySearch2(arr, mid + 1, r, target);
}

template<typename T>
int binarySearch2(T arr[], int n, T target){
	return __binarySearch2(arr, 0, n - 1, target);
}

// ���ֲ��ҷ�, ����������arr��, ����target
// ����ҵ�target, ���ص�һ��target��Ӧ������index
// ���û���ҵ�target, ���ر�targetС�����ֵ��Ӧ������, ���������ֵ�ж��, �����������
// ������target�������������СԪ��ֵ��ҪС, �򲻴������target��floorֵ, ����-1
template<typename T>
int floor(T arr[], int n, T target){

	assert(n >= 0);

	// Ѱ�ұ�targetС���������
	int l = -1, r = n - 1;
	while (l < r){
		// ʹ������ȡ��������ѭ��
		int mid = l + (r - l + 1) / 2;
		if (arr[mid] >= target)
			r = mid - 1;
		else
			l = mid;
	}

	assert(l == r);

	// ���������+1����target����, ������+1��Ϊ����ֵ
	if (l + 1 < n && arr[l + 1] == target)
		return l + 1;

	// ����, ��������Ϊ����ֵ
	return l;
}


// ���ֲ��ҷ�, ����������arr��, ����target
// ����ҵ�target, �������һ��target��Ӧ������index
// ���û���ҵ�target, ���ر�target�����Сֵ��Ӧ������, ��������Сֵ�ж��, ������С������
// ������target��������������Ԫ��ֵ��Ҫ��, �򲻴������target��ceilֵ, ������������Ԫ�ظ���n
template<typename T>
int ceil(T arr[], int n, T target){

	assert(n >= 0);

	// Ѱ�ұ�target�����С����ֵ
	int l = 0, r = n;
	while (l < r){
		// ʹ����ͨ������ȡ�����ɱ�����ѭ��
		int mid = l + (r - l) / 2;
		if (arr[mid] <= target)
			l = mid + 1;
		else // arr[mid] > target
			r = mid;
	}

	assert(l == r);

	// ���������-1����target����, ������+1��Ϊ����ֵ
	if (r - 1 >= 0 && arr[r - 1] == target)
		return r - 1;

	// ����, ��������Ϊ����ֵ
	return r;
}

#endif // _BINARYSEARCH_