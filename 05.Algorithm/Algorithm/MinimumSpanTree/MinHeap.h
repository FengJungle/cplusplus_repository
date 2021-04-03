#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include <cassert>

template<typename Item>
class MinHeap{
private:
	Item* data;
	int count;
	int capacity;

	void shiftUp(int k){
		while (k > 1 && data[k] < data[k / 2]){
			swap(data[k], data[k / 2]);
			k /= 2;
		}
	}
	void shiftDown(int k){
		while (2 * k <= count){
			int j = 2 * k;
			if (j + 1 <= count && data[j + 1] <= data[j]){
				j++;
			}
			if (data[k] <= data[j]){
				break;
			}
			swap(data[k], data[j]);
			k = j;
		}
	}
public:
	MinHeap(int capacity){
		this->capacity = capacity;
		data = new Item[capacity + 1];
		count = 0;
	}
	// 构造函数, 通过一个给定数组创建一个最小堆
	// 该构造堆的过程, 时间复杂度为O(n)
	MinHeap(Item arr[], int n){
		this->capacity = n;
		data = new Item[n + 1];
		count = n;

		for (int i = 0; i < n; i++){
			data[i + 1] = arr[i];
		}
		for (int i = count / 2; i >= 1; i--){
			shiftDown(i);
		}
	}
	~MinHeap(){
		delete[]data;
	}
	void insert(Item item){
		count++;
		data[count] = item;
		shiftUp(count);
	}
	Item extractMin(){
		assert(count > 0);
		Item ret = data[1];
		swap(data[1], data[count]);
		count--;
		shiftDown(1);
		return ret;
	}
	Item getMin(){
		assert(count > 0);
		return data[1];
	}
	int size(){
		return count;
	}
	bool empty(){
		return count == 0;
	}
};

#endif // _MIN_HEAP_H_