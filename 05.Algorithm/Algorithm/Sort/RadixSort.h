#ifndef _RADIX_SORT_
#define _RADIX_SORT_

int maxbit(int data[], int n) //���������������ݵ����λ��
{
	int maxData = data[0];        
	// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
	for (int i = 1; i < n; ++i)
	{
		if (maxData < data[i]){
			maxData = data[i];
		}
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;
}
// ��������
void RadixSort(int data[], int n) 
{
	int d = maxbit(data, n);
	int *tmp = new int[n];
	// ������
	int *count = new int[10]; 
	int i, j, k;
	int radix = 1;
	// ����d������
	for (i = 1; i <= d; i++) 
	{
		// ÿ�η���ǰ��ռ�����
		for (j = 0; j < 10; j++){
			count[j] = 0; 
		}
		// ͳ��ÿ��Ͱ�еļ�¼��
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; 
			count[k]++;
		}
		// ��tmp�е�λ�����η����ÿ��Ͱ
		for (j = 1; j < 10; j++){
			count[j] = count[j - 1] + count[j];
		}
		// ������Ͱ�м�¼�����ռ���tmp��
		for (j = n - 1; j >= 0; j--) 
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		// ����ʱ��������ݸ��Ƶ�data��
		for (j = 0; j < n; j++) {
			data[j] = tmp[j];
		}
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}

#endif // _RADIX_SORT_