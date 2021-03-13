#include <iostream>
#include <array>
using namespace std;

void testArray()
{
    // 列表初始化：声明时要指定array大小
    array<int, 10> arr_int = {1, 2, 3, 4, 5, 6, 7};
    // array<double, 10> arr_double{1.1, 2.2, 3.3, 4.4};

    // 可以将一个array赋值给另一个
    array<int, 10> arr2_int = arr_int;
    array<int, 10> arr3_int(arr_int);
    
    // 错误：array不支持此种初始化：10个元素，每个元素值为0
    // array<int, 10> arr4_int(10, 0);

    cout << "arr2_int.size:\t" << arr2_int.size() << endl;
    cout << "arr2_int.max_size:\t" << arr2_int.max_size() << endl;

    // data()返回数组的地址
    cout << "arr_int.data:\t" << arr_int.data() << endl;
    cout << "address of arr_int:\t" << &arr_int << endl;

    // 访问头部和尾部元素
    cout << "arr_int.front:\t" << arr_int.front() << endl;
    cout << "arr_int.back:\t" << arr_int.back() << endl;

    char ch[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    // array<char, 10> arr_char = ch; // Wrong
    // array<char, 10>arr_char(ch);   // Wrong
    // array<char, 10>arr_char{ch};   // Wrong
    array<char, 10> arr_char;
    for (auto i = 0; i < 10; i++)
    {
        arr_char[i] = ch[i];
    }

    // 迭代器遍历
    array<char, 10>::iterator ite = arr_char.begin();
    for (; ite != arr_char.end(); ite++)
    {
        cout << "\t" << *ite;
    }
    cout << endl;

    // Wrong, 大小必须与array大小一致
    // array<int,15>::iterator ite_int = arr2_int.rbegin();

    // Wrong, 此处应使用反向迭代器
    // array<int,10>::iterator ite_int = arr2_int.rbegin();
    array<int, 10>::reverse_iterator rite_int = arr2_int.rbegin();
    for (; rite_int != arr2_int.rend(); rite_int++)
    {
        // 可以通过迭代器修改元素的值
        *rite_int += 2;
        cout << "\t" << *rite_int;
    }
    cout << endl;

    // const迭代器，不允许修改内容
    array<int, 10>::const_iterator cite = arr2_int.begin() + 4;
    // 不允许修改
    // *cite = 5;
}

/*

容器的类型成员

iterator          此容器的迭代器类型

const_iterator    可以读取元素，但不能修改元素的迭代器类型

size_type         无符号整数类型，足够保存此种容器类型最大可能容器的大小

difference_type   带符号整数类型，足够保存两个迭代器之间的距离

value_type        元素类型

reference         元素的左值类型，与 value_type& 含义相同

const_reference   元素的const左值类型，即 const value_type&

*/
void test2()
{
    array<int,10> arr_int{1,2,3,4,5,6,7,8,9,10};
    array<int,10>::size_type tmp;
    tmp = arr_int[4];
    cout << tmp << endl;
}

void test3()
{
    array<double, 5> arr_double1 = {1.1,2.2,3.3};
    array<double, 4> arr_double2 = {1.1, 2.2, 3.4, 0};
    // if(arr_double1 == arr_double2)
    // {
    //     cout<<"arr_double1 == arr_double2"<<endl;
    // }
    // else if(arr_double1 > arr_double2)
    // {
    //     cout<<"arr_double1 > arr_double2"<<endl;
    // }
    // else{
    //     cout<<"arr_double1 < arr_double2"<<endl;
    // }
}

int main()
{
    testArray();

    // test2();

    test3();
}