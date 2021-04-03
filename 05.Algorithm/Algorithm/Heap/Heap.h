#ifndef _HEAP_
#define _HEAP_

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <time.h>

using namespace std;

/*=================DEFINITION=====================*/
template<typename Item>
class MaxHeap{
private:
	Item* data;
	int count;   // ���е�Ԫ������
	int capacity;

	void shiftUp(int k){
		while (k > 1 && data[k / 2] < data[k]){
			swap(data[k / 2], data[k]);
			k /= 2;
		}
	}

	void shiftDown(int k){
		// ��ǰ�����к��ӣ���һ�������ӣ���ȫ��������
		while (k * 2 <= count){
			int j = k * 2;// �ڴ���ѭ���У�data[k]��data[j]����λ��
			if (j + 1 <= count && data[j + 1] > data[j]){ // ��ǰ�������Һ���
				j = j + 1;
			}

			if (data[k] >= data[j]){
				break; // kԪ�ش���jԪ�ص�ʱ�򲻱ؽ�������ֹѭ��
			}
			swap(data[k], data[j]);
			k = j;
		}
	}
public:
	// ���캯��, ����һ���ն�, ������capacity��Ԫ��
	MaxHeap(int capacity){
		data = new Item[capacity + 1]; // �洢��������1��ʼ
		count = 0;
		this->capacity = capacity;
	}

	// heapify,�㷨���Ӷ���O(n)
	MaxHeap(Item arr[], int N){
		data = new Item[N + 1];
		this->capacity = N;
		for (int i = 0; i < N; i++){
			data[i + 1] = arr[i];
		}
		count = N;

		// Ѱ�Ҷ��е�һ������Ҷ�ӽڵ�Ľڵ㣬����shiftDown��������������
		// ��ȫ�����������ʣ���һ������Ҷ�ӽڵ�Ľڵ�����ֵΪcount/2
		for (int i = count / 2; i >= 1; i--){
			shiftDown(i);
		}
	}

	~MaxHeap(){
		delete[] data;
	}
	int size(){
		return count;
	}
	bool isEmpty(){
		return count == 0;
	}
	// ����Ԫ�أ����
	void insert(Item item){
		assert(count + 1 <= capacity);
		data[count + 1] = item;
		count++;
		shiftUp(count);
	}

	// ȡ������Ԫ�أ����ֵ
	Item getMax(){
		assert(count > 0);
		Item ret = data[1];

		swap(data[1], data[count]);
		count--;
		shiftDown(1);

		return ret;
	}
public:
	// ����״��ӡ�����ѽṹ
	void testPrint(){

		// testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
		if (size() >= 100){
			cout << "This print function can only work for less than 100 int";
			return;
		}

		// testPrintֻ�ܴ���������Ϣ
		if (typeid(Item) != typeid(int)){
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is: " << this->size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++){
			// ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
			assert(data[i] >= 0 && data[i] < 100);
			cout << data[i] << " ";
		}
		cout << endl;
		cout << endl;

		int n = size();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) {
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}

		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++){
			string line1 = string(max_level_number * 3 - 1, ' ');

			int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++){
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			cout << line1 << endl;

			if (level == max_level - 1)
				break;

			string line2 = string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			cout << line2 << endl;

			cur_tree_max_level_number /= 2;
		}
	}
private:
	void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		assert(offset + 1 < line.size());
		if (num >= 10) {
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else{
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	void putBranchInLine(string &line, int index_cur_level, int cur_tree_width){

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		assert(offset_left + 1 < line.size());
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		assert(offset_right < line.size());

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}
};
/*=================DEFINITION=====================*/

/*=================DEFINITION=====================*/
// ������
template<typename Item>
class IndexMaxHeap{
private:
	Item* data;
	// ����
	int* indices;
	// reverse[i]��ʾ����i�ڶ��е�λ��
	int* reverse;
	int count;   // ���е�Ԫ������
	int capacity;

	void shiftUp(int k){
		while (k > 1 && data[indices[k / 2]] < data[indices[k]]){
			swap(indices[k / 2], indices[k]);
			reverse[indices[k / 2]] = k / 2;
			reverse[indices[k]] = k;
			k /= 2;
		}
	}

	void shiftDown(int k){
		// ��ǰ�����к��ӣ���һ�������ӣ���ȫ��������
		while (k * 2 <= count){
			int j = k * 2;// �ڴ���ѭ���У�data[k]��data[j]����λ��
			if (j + 1 <= count && data[indices[j + 1]] > data[indices[j]]){ // ��ǰ�������Һ���
				j = j + 1;
			}

			if (data[indices[k]] >= data[indices[j]]){
				break; // kԪ�ش���jԪ�ص�ʱ�򲻱ؽ�������ֹѭ��
			}
			swap(indices[k], indices[j]);
			reverse[indices[j]] = j;
			reverse[indices[k]] = k;
			k = j;
		}
	}
public:
	// ���캯��, ����һ���ն�, ������capacity��Ԫ��
	IndexMaxHeap(int capacity){
		data = new Item[capacity + 1]; // �洢��������1��ʼ
		indices = new int[capacity + 1];
		reverse = new int[capacity + 1];
		for (int i = 0; i <= capacity; i++){
			reverse[i] = 0;
		}
		count = 0;
		this->capacity = capacity;
	}


	~IndexMaxHeap(){
		delete[] data;
		delete[] indices;
		delete[] reverse;
	}
	int size(){
		return count;
	}
	bool isEmpty(){
		return count == 0;
	}
	// ����Ԫ�أ����
	// ���� i:�����û����ԣ�i��0��ʼ
	void insert(int i, Item item){
		assert(count + 1 <= capacity);
		assert(i + 1 >= 1 && i + 1 <= capacity);

		i += 1;
		data[i] = item;
		indices[count + 1] = i;
		reverse[i] = count + 1;
		count++;
		shiftUp(count);
	}

	// ȡ������Ԫ�أ����ֵ
	Item getMax(){
		assert(count > 0);
		Item ret = data[indices[1]];

		swap(indices[1], indices[count]);
		reverse[indices[1]] = 1;
		reverse[indices[count]] = 0;
		count--;
		shiftDown(1);

		return ret;
	}

	// �������Ԫ�ص�����
	int extractMaxIndex(){
		assert(count > 0);
		// �ⲿ�û����ԣ���0��ʼ
		int index = indices[1] - 1;
		swap(indices[1], indices[count]);
		reverse[indices[1]] = 1;
		reverse[indices[count]] = 0;
		count--;
		shiftDown(1);
		
		return index;
	}

	// �ж϶����Ƿ��������i
	bool contain(int i){
		assert(i + 1 >= 1 && i + 1 <= capacity);
		return reverse[i + 1] != 0;
	}

	Item getItem(int i){
		assert(contain(i));
		return data[i + 1];
	}

	void change(int i, Item newItem){
		assert(contain(i));
		i += 1;
		data[i] = newItem;
		//// �ҵ�indices[j] = i�� j��ʾdata[i]�ڶ��е�λ��
		//for (int j = 1; j <= count; j++){
		//	if (indices[j] == i){
		//		shiftUp(j);
		//		shiftDown(j);
		//		return;
		//	}
		//}
		int j = reverse[i];
		shiftUp(j);
		shiftDown(j);
	}
public:
	// ����״��ӡ�����ѽṹ
	void testPrint(){

		// testPrintֻ�ܴ�ӡ100��Ԫ�����ڵĶѵ���״��Ϣ
		if (size() >= 100){
			cout << "This print function can only work for less than 100 int";
			return;
		}

		// testPrintֻ�ܴ���������Ϣ
		if (typeid(Item) != typeid(int)){
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is: " << this->size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++){
			// ���ǵ�testPrintҪ����е�����������[0, 100)�ķ�Χ��
			assert(data[i] >= 0 && data[i] < 100);
			cout << data[i] << " ";
		}
		cout << endl;
		cout << endl;

		int n = size();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) {
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}

		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++){
			string line1 = string(max_level_number * 3 - 1, ' ');

			int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++){
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			cout << line1 << endl;

			if (level == max_level - 1)
				break;

			string line2 = string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			cout << line2 << endl;

			cur_tree_max_level_number /= 2;
		}
	}
private:
	void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		assert(offset + 1 < line.size());
		if (num >= 10) {
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else{
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	void putBranchInLine(string &line, int index_cur_level, int cur_tree_width){

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		assert(offset_left + 1 < line.size());
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		assert(offset_right < line.size());

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}
};
/*=================DEFINITION=====================*/

/*=====================TEST=======================*/
#if 0
int main()
{
	MaxHeap<int> H = MaxHeap<int>(100);
	cout << H.isEmpty() << endl;
	cout << H.size() << endl;

	// 1. �������15��Ԫ��
	cout << " 1. �������15��Ԫ��" << endl;
	srand(time(NULL));
	for (int i = 0; i < 15; i++){
		H.insert(rand() % 100);
	}
	H.testPrint();
	cout << endl;

	// 2. ȡ���Ѷ�
	cout << " 2. ȡ���Ѷ�" << endl;
	while (false == H.isEmpty()){
		int i = H.getMax();
		cout << i << "  ";
	}

	cout << endl;

	system("pause");
}
#endif
/*=====================TEST=======================*/

#endif // _HEAP_
