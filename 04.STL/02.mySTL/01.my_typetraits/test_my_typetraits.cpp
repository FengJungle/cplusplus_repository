/*

File Name:   test_my_typetraits.h
Description: 测试_my_type_traits
Date:        2020/11/29
Author:      Feng Qiangguo

*/

#include <iostream>
using namespace std;

#include "my_typetraits.h"
using namespace mySTL;

// func_helper的入口参数并无其他作用
void func_helper(__my_false_type)
{
    cout<<"enter func_helper(__my_false_type)"<<endl;
}

void func_helper(__my_true_type)
{
    cout<<"enter func_helper(__my_true_type)"<<endl;
}

template<typename T>
void func(T a)
{
    // typename 用于指明is_POD_type是一个类型名
    typedef typename my_type_traits<T>::_is_POD_type _is_pod_type;

    // _is_pod_type()产生一个_is_pod_type类型的临时对象，作为参数传递给func_helper()
    func_helper(_is_pod_type()); 
}

int main(int argc, char* argv[])
{
    // 基本上数据类型是POD
    func(10);
    func('A');
    func(1.29f);
    func(false);
    // class A定义了构造函数，不是pod
    func(A());

    return 0;
}