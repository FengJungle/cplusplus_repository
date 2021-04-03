#include <iostream>

/*

File Name:   test_array.cpp
Description: 测试my_array
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "my_array.h"
using namespace mySTL;

class A_
{
public:
    A_(int ia = 0) : a(ia)
    {
    }
    friend ostream &operator<<(ostream &os, const A_ &_a);

private:
    int a;
};

ostream& operator<<(ostream& os, const A_& _a)
{
    os << _a.a << " ";
    return os;
}

void test_self_defined_class()
{
    my_array<A_, 5> arr{A_(44), A_(55),A_(66), A_(77)};
    cout << "arr.size():" << arr.size() << endl;
    for (auto i = arr.begin(); i != arr.end(); i++)
    {
        cout << *i;
    }
    cout << endl;
    cout << arr.back() << endl;
    cout << arr.front() << endl;
}

void testArray()
{
    // 列表初始化：声明时要指定array大小
    my_array<int, 10> arr_int = {1, 2, 3, 4, 5, 6, 7};
    my_array<double, 10> arr_double{1.1, 2.2, 3.3, 4.4};

    // 可以将一个array赋值给另一个
    my_array<int, 10> arr2_int = arr_int;
    my_array<int, 10> arr3_int(arr_int);

    // 错误：array不支持此种初始化：10个元素，每个元素值为0
    // array<int, 10> arr4_int(10, 0);

    cout << "arr2_int.size:\t" << arr2_int.size() << endl;
    cout << "arr3_int.max_size:\t" << arr3_int.max_size() << endl;

    // data()返回数组的地址
    cout << "arr_int.data:\t" << arr_int.data() << endl;
    cout << "address of arr_int:\t" << &arr_int << endl;

    // 访问头部和尾部元素
    cout << "arr_int.front:\t" << arr_int.front() << endl;
    cout << "arr_int.back:\t" << arr_int.back() << endl;

    char ch[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    my_array<char, 10> arr_char;
    for (auto i = 0; i < 10; i++)
    {
        arr_char[i] = ch[i];
    }

    // 迭代器遍历
    my_array<char, 10>::iterator ite = arr_char.begin();
    for (; ite != arr_char.end() - 4; ite++)
    {
        cout << "\t" << *ite;
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    // testArray();

    test_self_defined_class();

    return 0;
}
