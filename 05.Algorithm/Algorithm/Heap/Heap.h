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
	int count;   // 堆中的元素数量
	int capacity;

	void shiftUp(int k){
		while (k > 1 && data[k / 2] < data[k]){
			swap(data[k / 2], data[k]);
			k /= 2;
		}
	}

	void shiftDown(int k){
		// 当前孩子有孩子，就一定有左孩子（完全二叉树）
		while (k * 2 <= count){
			int j = k * 2;// 在此轮循环中，data[k]和data[j]交换位置
			if (j + 1 <= count && data[j + 1] > data[j]){ // 当前孩子有右孩子
				j = j + 1;
			}

			if (data[k] >= data[j]){
				break; // k元素大于j元素的时候不必交换，终止循环
			}
			swap(data[k], data[j]);
			k = j;
		}
	}
public:
	// 构造函数, 构造一个空堆, 可容纳capacity个元素
	MaxHeap(int capacity){
		data = new Item[capacity + 1]; // 存储的索引从1开始
		count = 0;
		this->capacity = capacity;
	}

	// heapify,算法复杂度是O(n)
	MaxHeap(Item arr[], int N){
		data = new Item[N + 1];
		this->capacity = N;
		for (int i = 0; i < N; i++){
			data[i + 1] = arr[i];
		}
		count = N;

		// 寻找堆中第一个不是叶子节点的节点，进行shiftDown操作，构建最大堆
		// 完全二叉树的性质：第一个不是叶子节点的节点索引值为count/2
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
	// 插入元素：入队
	void insert(Item item){
		assert(count + 1 <= capacity);
		data[count + 1] = item;
		count++;
		shiftUp(count);
	}

	// 取出树顶元素：最大值
	Item getMax(){
		assert(count > 0);
		Item ret = data[1];

		swap(data[1], data[count]);
		count--;
		shiftDown(1);

		return ret;
	}
public:
	// 以树状打印整个堆结构
	void testPrint(){

		// testPrint只能打印100个元素以内的堆的树状信息
		if (size() >= 100){
			cout << "This print function can only work for less than 100 int";
			return;
		}

		// testPrint只能处理整数信息
		if (typeid(Item) != typeid(int)){
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is: " << this->size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++){
			// 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
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
// 索引堆
template<typename Item>
class IndexMaxHeap{
private:
	Item* data;
	// 索引
	int* indices;
	// reverse[i]表示索引i在堆中的位置
	int* reverse;
	int count;   // 堆中的元素数量
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
		// 当前孩子有孩子，就一定有左孩子（完全二叉树）
		while (k * 2 <= count){
			int j = k * 2;// 在此轮循环中，data[k]和data[j]交换位置
			if (j + 1 <= count && data[indices[j + 1]] > data[indices[j]]){ // 当前孩子有右孩子
				j = j + 1;
			}

			if (data[indices[k]] >= data[indices[j]]){
				break; // k元素大于j元素的时候不必交换，终止循环
			}
			swap(indices[k], indices[j]);
			reverse[indices[j]] = j;
			reverse[indices[k]] = k;
			k = j;
		}
	}
public:
	// 构造函数, 构造一个空堆, 可容纳capacity个元素
	IndexMaxHeap(int capacity){
		data = new Item[capacity + 1]; // 存储的索引从1开始
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
	// 插入元素：入队
	// 索引 i:传入用户而言，i从0开始
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

	// 取出树顶元素：最大值
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

	// 返回最大元素的索引
	int extractMaxIndex(){
		assert(count > 0);
		// 外部用户而言，从0开始
		int index = indices[1] - 1;
		swap(indices[1], indices[count]);
		reverse[indices[1]] = 1;
		reverse[indices[count]] = 0;
		count--;
		shiftDown(1);
		
		return index;
	}

	// 判断堆中是否存在索引i
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
		//// 找到indices[j] = i， j表示data[i]在堆中的位置
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
	// 以树状打印整个堆结构
	void testPrint(){

		// testPrint只能打印100个元素以内的堆的树状信息
		if (size() >= 100){
			cout << "This print function can only work for less than 100 int";
			return;
		}

		// testPrint只能处理整数信息
		if (typeid(Item) != typeid(int)){
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is: " << this->size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++){
			// 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
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

	// 1. 随机插入15个元素
	cout << " 1. 随机插入15个元素" << endl;
	srand(time(NULL));
	for (int i = 0; i < 15; i++){
		H.insert(rand() % 100);
	}
	H.testPrint();
	cout << endl;

	// 2. 取出堆顶
	cout << " 2. 取出堆顶" << endl;
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
