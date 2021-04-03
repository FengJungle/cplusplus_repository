#ifndef _SORTTESTHELPER_H_
#define _SORTTESTHELPER_H_

#include <iostream>
#include <ctime>
#include <cassert>
#include <string>
using namespace std;

namespace SortTestHelper{
	// 生成有n个元素的随机数组，每个元素的随机范围为[rangeL, rangeR]
	int* generateRandomArray(int n, int rangeL, int rangeR){
		assert(rangeL <= rangeR);
		int *arr = new int[n];

		// 设置随机种子
		srand(time(NULL));
		for (int i = 0; i < n; i++){
			// 生成随机数
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;
	}

	// 生成近乎有序的数据
	int* generateNearlyOrderedArray(int n, int swapTimes){
		int *arr = new int[n];
		for (int i = 0; i < n; i++){
			arr[i] = i;
		}
		srand(time(NULL));
		for (int i = 0; i < swapTimes; i++){
			int posx = rand() % n;
			int posy = rand() % n;
			swap(posx, posy);
		}
		return arr;
	}

	template<typename T>
	bool isSorted(T arr[], int n){
		for (int i = 0; i < n-1; i++){
			if (arr[i] > arr[i + 1]){
				return false;
			}
		}
		return true;
	}

	// 测试函数性能
	template<typename T>
	void testSort(string sortName, void(*sort)(T[], int), T arr[], int n){
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));
		cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}

	// 打印数组元素
	template<typename T>
	void printArr(T arr[], int n){
		for (int i = 0; i < n; i++){
			cout << arr[i] << "  ";
		}
		cout << endl;
	}

	int* copyIntArr(int inputArr[], int n){
		int* outputArr = new int[n];
		memcpy(outputArr, inputArr, sizeof(int)*n);
		return outputArr;
	}
}

#endif // _SORTTESTHELPER_H_