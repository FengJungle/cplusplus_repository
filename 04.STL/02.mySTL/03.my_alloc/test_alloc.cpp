/*

File Name:   test_alloc.h
Description: 测试alloc
Date:        2020/12/03
Author:      Feng Qiangguo

*/

#include "construct.h"
#include "alloc.h"
#include "uninitialized.h"
#include <iostream>
#include <vector>
using namespace std;
// using namespace mySTL;

// 测试construct和destroy
void test_construct()
{
    // 1. Test: int
    int a[3] = {0};

    mySTL::construct<int, int>(a, 10);
    mySTL::construct<int, int>(&a[1], int(20));
    mySTL::construct<int, int>(&a[2], 30);
    cout << a[0] << " " << a[1] << " " << a[2] << endl;

    mySTL::destroy(&a[1]);
    mySTL::destroy(&a[2]);
    mySTL::destroy(&a[3]);

    // 2. Test: vector
    vector<float> v(5);
    float f[5] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    for (int i = 0; i < 5; i++)
    {
        mySTL::construct(&(*(v.begin() + i)), f[i]);
        cout << v[i] << endl;
    }

    for (int i = 0; i < 5; i++)
    {
        mySTL::destroy(v.begin(), v.end());
    }

    // 3. Test: class
    class A
    {
    public:
        A(int ia) : a(ia) { cout << "constructor" << endl; }
        ~A() { cout << "destructor" << endl; }
        void show() { cout << "a = " << a << endl; }

    private:
        int a;
    };
    A tmp(10);
    tmp.show();
    A tmp2(0);
    mySTL::construct(&tmp2, tmp);
    tmp2.show();
    mySTL::destroy(&tmp2);
}

// 测试alloc
void test_alloc()
{
    mySTL::alloc Alloc;
    Alloc.printMemoryInfo(); // heap_size = 0

    int *a = (int *)(Alloc.allocate(sizeof(int)));

    Alloc.deallocate(a, sizeof(int));
    Alloc.printMemoryInfo(); // heap_size = 320

    void *p = Alloc.allocate(540); // 540 > 128, 直接从第一级配置器分配内存，所以heap_size = 320
    Alloc.printMemoryInfo();

    Alloc.deallocate(p, 540);
    Alloc.printMemoryInfo();
}

void test_uninitialized_func()
{
    int arr[5] = {10, 2, 3, 4, 34};
    vector<int> arr2(5);
    mySTL::uninitialized_copy(arr, arr + 5, arr2.begin());
    for (int i = 0; i < 5; i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    float arr3[10] = {0.00f};
    mySTL::uninitialized_fill(arr3, arr3 + 10, 4.5f);
    for (int i = 0; i < 10; i++)
    {
        cout << arr3[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{

    // test_construct();

    // test_alloc();

    test_uninitialized_func();

    return 0;
}