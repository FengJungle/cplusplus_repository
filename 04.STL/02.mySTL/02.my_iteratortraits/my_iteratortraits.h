#ifndef __MY_ITERATOR_TRAITS_H__
#define __MY_ITERATOR_TRAITS_H__
/*

File Name:   my_iteratortraits.h
Description: 定义my_iteratortraits
Date:        2020/11/29
Author:      Feng Qiangguo

*/

/*

my_iteratortraits萃取 迭代器型别(type) 特性

迭代器型别特性：迭代器所指之物的型别
my_iteratortraits扮演“特性萃取机”的角色，萃取各个迭代器的特性，即迭代器的相应型别。
为使这个特性萃取剂能够标识出不同迭代器的型别，各个迭代器内部必须以 内嵌型别定义 的方式定义出相应型别
根据STL，迭代器常用到的型别有5种：

1. iterator_category ：迭代器类型 
    input iterator: 只读，不允许改变迭代器所指的对象
    Output iterator: 只写
    Forward iterator: 允许写入型算法在此种迭代器所形成的区间上进行读写操作
    Bidirectional iterator: 可双向移动
    Random Access Iterator: 涵盖所有算术能力
2. value_type        : 迭代器所指对象的型别。任何一个打算与STL算法有完美搭配的class，都应定义自己的value type内嵌型别
3. difference_type   ：表示两个迭代器之间的距离
4. pointer           ：指针
5. reference         ：引用

*/

namespace mySTL
{
    #include <stddef.h>

    struct my_input_iterator_tag
    {
    };
    struct my_output_iterator_tag
    {
    };
    struct my_forward_iterator_tag : public my_input_iterator_tag
    {
    };
    struct my_bidirectional_iterator_tag : public my_forward_iterator_tag
    {
    };
    struct my_random_access_iterator_tag : public my_bidirectional_iterator_tag
    {
    };

    // 自行开发的迭代器最好继承自下面这个iterator
    template <typename Category,
              typename T,
              typename Distance = ptrdiff_t,
              typename Pointer = T *,
              typename Reference = T &>
    struct my_iterator
    {
        typedef Category  _iterator_category;
        typedef T         _value_type;
        typedef Distance  _difference_type;
        typedef Pointer   _pointer;
        typedef Reference _reference;
    };

    // 泛型
    template<typename Iterator>
    struct my_iterator_traits
    {
        typedef typename Iterator::iterator_category _iterator_category;
        typedef typename Iterator::value_type        _value_type;
        typedef typename Iterator::difference_type   _difference_type;
        typedef typename Iterator::pointer           _pointer;
        typedef typename Iterator::reference         _reference;
    };
    // 特化：原生指针
    template<typename T>
    struct my_iterator_traits<T*>
    {
        typedef my_random_access_iterator_tag _iterator_category;
        typedef T _value_type;
        typedef ptrdiff_t _difference_type;
        typedef T *_pointer;
        typedef T &_reference;
    };
    // 特化：原生指针 pointer-to-const
    template<typename T>
    struct my_iterator_traits<const T*>
    {
        typedef my_random_access_iterator_tag _iterator_category;
        typedef T _value_type;
        typedef ptrdiff_t _difference_type;
        typedef const T* _pointer;
        typedef const T& _reference;
    };
    
    // 萃取迭代器的category
    template<typename Iterator>
    typename my_iterator_traits<Iterator>::_iterator_category 
    iterator_category(const Iterator& It)
    {
        typedef typename my_iterator_traits<Iterator>::my_iterator_category category;
        return category();
    }

    // 萃取迭代器的value_type
    template<typename Iterator>
    typename my_iterator_traits<Iterator>::_value_type*
    value_type(const Iterator& It)
    {
        return static_cast<typename my_iterator_traits<Iterator>::_value_type*>(0);
    }

    // 萃取迭代器的distance_type
    template<typename Iterator>
    typename my_iterator_traits<Iterator>::_difference_type*
    distance_type(const Iterator& It)
    {
        return static_cast<typename my_iterator_traits<Iterator>::_difference_type*>(0);
    }
   

} // namespace mySTL

#endif // __MY_ITERATOR_TRAITS_H__