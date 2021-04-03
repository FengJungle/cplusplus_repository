#ifndef _SORTTESTHELPER_H_
#define _SORTTESTHELPER_H_

#include <iostream>
#include <ctime>
#include <cassert>
#include <string>
using namespace std;

namespace SortTestHelper{
	// ������n��Ԫ�ص�������飬ÿ��Ԫ�ص������ΧΪ[rangeL, rangeR]
	int* generateRandomArray(int n, int rangeL, int rangeR){
		assert(rangeL <= rangeR);
		int *arr = new int[n];

		// �����������
		srand(time(NULL));
		for (int i = 0; i < n; i++){
			// ���������
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;
	}

	// ���ɽ������������
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

	// ���Ժ�������
	template<typename T>
	void testSort(string sortName, void(*sort)(T[], int), T arr[], int n){
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));
		cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	}

	// ��ӡ����Ԫ��
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