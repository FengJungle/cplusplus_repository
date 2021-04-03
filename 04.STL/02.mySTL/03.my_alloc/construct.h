#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

/*

File Name:   construct.h
Description: construct, destroy
Date:        2020/11/30
Author:      Feng Qiangguo

*/

#include <new.h>
#include "../01.my_typetraits/my_typetraits.h"
#include "../02.my_iteratortraits/my_iteratortraits.h"

namespace mySTL
{
    template <typename T1, typename T2>
    inline void construct(T1 *p, const T2 &value)
    {
        new (p) T1(value); // placement new 定位new
    }

    template <typename T>
    inline void destroy(T *pointer)
    {
        // 调用析构函数
        pointer->~T();
    }

    // non-trivial-destructor
    template <typename ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __my_false_type)
    {
        for (; first < last; ++first)
        {
            destroy(&*first);
        }
    }

    // trivial-destructor
    template <typename ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __my_true_type)
    {
        // Do nothing
    }

    // 判断元素型别(value type)
    template <typename ForwardIterator, typename T>
    inline void __destroy(ForwardIterator first, ForwardIterator last, T *)
    {
        typedef typename my_type_traits<T>::_has_trivial_destructor trivial_destructor;
        __destroy_aux(first, last, trivial_destructor());
    }

    template <typename ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last)
    {
        __destroy(first, last, value_type(first));
    }

    // 针对char*和wchar_t*的特化版本
    inline void destroy(char *, char *) {}
    inline void destroy(wchar_t *, wchar_t *) {}
} // namespace mySTL

#endif // _CONSTRUCT_H_