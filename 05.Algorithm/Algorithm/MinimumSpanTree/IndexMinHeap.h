#ifndef _INDEX_MIN_HEAP_H_
#define _INDEX_MIN_HEAP_H_

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename Item>
class IndexMinHeap{
private:
	int count;
	int capacity;
	Item* data;
	int*  indexes;
	int* reverse;

	void shiftDown(int k){
		while (2 * k <= count){
			int j = 2 * k;
			if (j + 1 <= count && data[indexes[j + 1]] < data[indexes[j]]){
				j++;
			}
			if (data[indexes[k]] <= data[indexes[j]]){
				break;
			}
			swap(indexes[k], indexes[j]);
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;
		}
	}

	void shiftUp(int k){
		while (k > 1 && data[indexes[k]] < data[indexes[k / 2]]){
			swap(indexes[k], indexes[k / 2]);
			reverse[indexes[k]] = k;
			reverse[indexes[k/2]] = k/2;
			k /= 2;
		}
	}

public:
	IndexMinHeap(int capacity){
		this->count = 0;
		this->capacity = capacity;
		data = new Item[capacity + 1];
		indexes = new int[capacity + 1];
		reverse = new int[capacity + 1];

		for (int i = 0; i <= capacity; i++){
			reverse[i] = 0;
		}
	}
	void insert(int index, Item item){
		index += 1;
		data[index] = item;

		indexes[count + 1] = index;
		reverse[indexes[count + 1]] = count + 1;
		count++;
		shiftUp(count);
	}

	int extractMinIndex(){
		int ret = indexes[1] - 1;
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;
		count--;
		shiftDown(1);
		return ret;
	}

	Item extractMin(){
		Item ret = data[indexes[1]];
		swap(indexes[1], indexes[count]);
		reverse[indexes[1]] = 1;
		reverse[indexes[count]] = 0;
		count--;
		shiftDown(1);
		return ret;
	}

	Item getItem(int index){
		return data[indexes[index + 1]];
	}

	void change(int index, Item item){
		index += 1;
		data[index] = item;
		shiftDown(reverse[index]);
		shiftUp(reverse[index]);
	}

	int size(){
		return count;
	}
	bool empty(){
		return count == 0;
	}
	~IndexMinHeap(){
		delete[] data;
		delete[] indexes;
		delete[] reverse;
	}
};

#endif // _INDEX_MIN_HEAP_H_