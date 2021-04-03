#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

/*

File Name:   uninitialized.h
Description: 内存处理基本工具
Date:        2020/12/03
Author:      Feng Qiangguo

*/

#include "../01.my_typetraits/my_typetraits.h"
#include "../02.my_iteratortraits/my_iteratortraits.h"
// 会使用到STL的算法
using namespace std;
#include <algorithm>

/*
 
STL定义了5个全局函数，作用于未初始化的空间上：
1. construct()
2. destroy()
3. uninitialized_coopy()
4. uninitialized_fill()
5. uninitialized_fill_n()

*/

namespace mySTL
{
    // 是POD，采用STL的copy算法
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(
        InputIterator first,
        InputIterator last,
        ForwardIterator result,
        __my_true_type)
    {
        return copy(first, last, result);
    }

    // 不是POD，拷贝构造
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator __uninitialized_copy_aux(
        InputIterator first,
        InputIterator last,
        ForwardIterator result,
        __my_false_type)
    {
        ForwardIterator cur = result;
        for (; first != last; ++first, ++cur)
        {
            construct(&*cur, *first);
        }
        return cur;
    }

    // 辅助函数：1. 利用value_type萃取出first的value_type
    //          2. 判断是否是POD，根据判断结果采取不同的copy方法
    template <typename InputIterator, typename ForwardIterator, typename T>
    inline ForwardIterator __uninitialized_copy(
        InputIterator first,
        InputIterator last,
        ForwardIterator result,
        T *)
    {
        typedef typename my_type_traits<T>::_is_POD_type isPOD;
        return __uninitialized_copy_aux(first, last, result, isPOD());
    }

    /*
    *  输入：[first, last)
    *  输出：[result, result + (last - first))
    *  如果输出范围内的每一个迭代器都指向未初始化区域，uninitialized_copy()会调用拷贝构造函数，
    *  从输入范围内为每个对象产生一个复制品，放入输出范围中
    */
    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator uninitialized_copy(
        InputIterator first,
        InputIterator last,
        ForwardIterator result)
    {
        // 辅助函数，利用value_type()萃取出first的value_type
        return __uninitialized_copy(first, last, result, value_type(first));
    }

    /*************************************************************************************/

    // 是POD，调用STL的fill()算法
    template <typename ForwardIterator, typename T>
    inline void __uninitialized_fill_aux(
        ForwardIterator first,
        ForwardIterator last,
        const T &val,
        __my_true_type)
    {
        fill(first, last, val);
    }

    // 不是POD，调用拷贝构造函数
    template <typename ForwardIterator, typename T>
    inline void __uninitialized_fill_aux(
        ForwardIterator first,
        ForwardIterator last,
        const T &val,
        __my_false_type)
    {
        for (; first < last; ++first)
        {
            construct(&*first, val);
        }
    }

    // 辅助函数：1. 利用value_type萃取出first的value_type
    //          2. 判断是否是POD，根据判断结果采取不同的fill方法
    template <typename ForwardIterator, typename T, typename T1>
    inline void __uninitialized_fill(
        ForwardIterator first,
        ForwardIterator last,
        const T &val,
        T1 *)
    {
        typedef typename my_type_traits<T1>::_is_POD_type isPOD;
        __uninitialized_fill_aux(first, last, val, isPOD());
    }

    /*
    * 如果[first, last)范围内的每一个迭代器都指向未初始化内存，
    * 那么uninitialized_fill()会针对操作范围内的每个迭代器i，调用construct(&*i, val)
    */
    template <typename ForwardIterator, typename T>
    void uninitialized_fill(
        ForwardIterator first,
        ForwardIterator last,
        const T &val)
    {
        __uninitialized_fill(first, last, val, value_type(first));
    }

    /*************************************************************************************/

    // 是POD，交给高阶函数完成
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator __uninitialized_fill_n_aux(
        ForwardIterator first,
        Size n,
        const T &val,
        __my_true_type)
    {
        return fill_n(first, n, val);
    }

    // 不是POD，交给construct()完成
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator __uninitialized_fill_n_aux(
        ForwardIterator first,
        Size n,
        const T &val,
        __my_false_type)
    {
        ForwardIterator cur = first;
        for (; n > 0; --n, ++cur)
        {
            construct(&*cur, val);
        }
        return cur;
    }

    // 辅助函数：1. 利用value_type萃取出first的value_type
    //          2. 判断是否是POD，根据判断结果采取不同的fill方法
    template <typename ForwardIterator, typename Size, typename T, typename T1>
    inline ForwardIterator __uninitialized_fill_n(
        ForwardIterator first,
        Size n,
        const T &val,
        T1 *)
    {
        typedef typename my_type_traits<T1>::_is_POD_type is_POD;
        return __uninitialized_fill_n_aux(first, n, val, is_POD());
    }

    /*
    * 如果[first, first + n)范围内的每一个迭代器都指向未初始化内存，
    * uninitialized_fill_n()会针对操作范围内的每个迭代器i，调用construct(&*i, val)
    */
    template <typename ForwardIterator, typename Size, typename T>
    ForwardIterator uninitialized_fill_n(
        ForwardIterator first,
        Size n,
        const T &val)
    {
        // 辅助函数，利用value_type()萃取出first的value_type
        return __uninitialized_fill_n(first, n, val, value_type(first));
    }

} // namespace mySTL

#endif // _UNINITIALIZED_H_