#include <iostream>
#include <vector>
using namespace std;

/*

heap底层实现就是vector
priority_queue底层实现是heap

*/

// 遍历vector
void print(vector<int> &arr)
{
    vector<int>::const_iterator cite = arr.begin();
    // auto cite = arr.begin();
    for (; cite != arr.end(); cite++)
    {
        cout << "\t" << *cite;
    }
    cout << endl;
}

/*

Test 1: vector的声明和初初始化

*/
void test1()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // vector<int> vec_int = arr;   // wrong
    // vector<int>vec_int(arr);     // wrong

    // 声明一个vector，包含10个元素，初始值均为1
    vector<int> vec_int(10, 1);
    // 声明一个vector，包含10个元素，默认初始值
    vector<int> vec_int2(10);

    // 列表初始化
    vector<int> vec_int3 = {1, 2, 3, 4, 5};
    vector<int> vec_int4{6, 7, 8, 9, 10};

    // 赋值
    vector<int> vec_int5 = vec_int3;
    vector<int> vec_int6(vec_int4);
}

/*

Test 2: vector基本操作

*/

void test2()
{
    vector<int> vec_int{1, 2, 3, 4, 5};
    cout << "size:\t" << vec_int.size() << endl;
    cout << "capacity:\t" << vec_int.capacity() << endl;
    cout << "max_size:\t" << vec_int.max_size() << endl;
    cout << "data:\t" << vec_int.data() << endl;

    // 随机访问元素
    vector<int>::value_type i = vec_int[3];
    cout << i << endl;

    cout << "vec_int.at(4):\t" << vec_int.at(4) << endl;
    cout << "vec_int[2]:\t" << vec_int[2] << endl;
    cout << "vec_int.front():\t" << vec_int.front() << endl;
    cout << "vec_int.back():\t" << vec_int.back() << endl;

    // 尾部添加元素
    vec_int.push_back(10);
    vec_int.push_back(11);
    print(vec_int);

    // Wrong, vector不允许在头部添加
    // vec_int.push_front(10);

    int arr[] = {10, 20, 30, 40};
    vector<int> arr_temp = {11, 22, 33, 44};
    // 在vector指定位置插入指定范围的元素
    vec_int.insert(vec_int.begin(), arr, arr + 3);
    print(vec_int);

    vec_int.insert(vec_int.begin(), arr_temp.begin(), arr_temp.begin() + 2);
    print(vec_int);

    // 在vector的起始位置插入10个值为15的元素
    vec_int.insert(vec_int.begin(), 10, 15);
    print(vec_int);

    // 在指定位置添加元素99
    vec_int.insert(vec_int.begin() + 4, 99);
    print(vec_int);

    // 删除指定范围元素
    vec_int.erase(vec_int.begin(), vec_int.begin() + 4);
    print(vec_int);

    // 删除尾部元素
    vec_int.pop_back();
    vec_int.pop_back();
    // vec_int.pop_front();  // vector不支持pop_front()

    // 清空
    vec_int.clear();
}

/*

Test3: 查找和排序

*/
#include <algorithm>

void test3()
{
    vector<int> arr = {9, 23, 12, 0, 132, 3, 43, 29, 54, 87, 332};
    print(arr);

    // 查找
    auto ite = ::find(arr.begin(), arr.end(), 12);
    if (ite != arr.end())
    {
        cout << "find 12:" << endl;
    }
    else
    {
        cout << "not found!" << endl;
    }

    // 排序 
    sort(arr.begin(), arr.end());
    print(arr);
}

int main()
{

    // test1();

    // test2();
    
    test3();

    return 0;
}