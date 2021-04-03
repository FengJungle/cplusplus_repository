#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <assert.h>
using namespace std;

template<typename Item>
class Queue{
public:
	Queue(int capacity);
	~Queue();
	void clear();
	bool empty() const;
	bool full() const;
	int size() const;
	bool enqueue(Item element);
	bool dequeue(Item &element);
	void traverse();
private:
	int capacity;
	int count;
	Item* data;
	int front;
	int rear;
};

template<typename Item>
Queue<Item>::Queue<Item>(int capacity){
	this->capacity = capacity;
	this->data = new Item[capacity];
	assert(data != NULL);
	this->clear();
}

template<typename Item>
Queue<Item>::~Queue<Item>(){
	delete[]data;
}

template<typename Item>
void Queue<Item>::clear(){
	front = 0;
	rear = 0;
	count = 0;
}

template<typename Item>
bool Queue<Item>::empty() const{
	return count == 0;
}

template<typename Item>
bool Queue<Item>::full() const{
	return count == capacity;
}

template<typename Item>
int Queue<Item>::size() const{
	return count;
}

template<typename Item>
bool Queue<Item>::enqueue(Item item){
	if (full()){
		cout << "queue is full" << endl;
		return false;
	}
	data[rear] = item;
	rear++;
	rear %= capacity;
	count++;
	return true;
}

template<typename Item>
bool Queue<Item>::dequeue(Item& item){
	if (empty()){
		cout << "queue is empty" << endl;
		return false;
	}
	item = data[front];
	front++;
	front %= capacity;
	count--;
	return true;
}

template<typename Item>
void Queue<Item>::traverse(){
	for (int i = front; i < front + count; i++){
		cout << data[i%capacity] << " ";
	}
	cout << endl;
}

#endif // _QUEUE_H_