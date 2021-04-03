#ifndef __MY_TYPE_TRAITS_H__
#define __MY_TYPE_TRAITS_H__
/*

File Name:   my_typetraits.h
Description: 定义_my_type_traits
Date:        2020/11/29
Author:      Feng Qiangguo

*/

/*

my_type_traits萃取型别(type)特性

型别特性：
(1). 这个型别是否具备non-trivial defalt constructor?
(2). 是否具备non-trival copy constructor?
(3). 是否具备non-trival assignment operator?
(4). 是否具备non-trival destructor?

如果答案是否定的，那我们在对这个型别进行构造、析构、拷贝、赋值等操作时，可以采用最有效率的措施，采用内存直接处理操作如malloc()，memcpy()等

*/

namespace mySTL
{
    struct __my_true_type
    {
    };
    struct __my_false_type
    {
    };

    // 泛型，默认均为__my_false_type，定义出最保守的值
    template <typename T>
    struct my_type_traits
    {
        // typedef __my_true_type this_dummy_member_must_be_first;
        typedef __my_false_type _has_trivial_default_constructor;
        typedef __my_false_type _has_trivial_copy_constructor;
        typedef __my_false_type _has_trivial_assignment_operator;
        typedef __my_false_type _has_trivial_destructor;
        typedef __my_false_type _is_POD_type;
    };
    // 模板偏特化，针对原生指针
    template <typename T>
    struct my_type_traits<T *>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 bool
    template <>
    struct my_type_traits<bool>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 char
    template <>
    struct my_type_traits<char>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 signed char
    template <>
    struct my_type_traits<signed char>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 unsigned char
    template <>
    struct my_type_traits<unsigned char>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 short
    template <>
    struct my_type_traits<short>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 unsigned short>
    template <>
    struct my_type_traits<unsigned short>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别int
    template <>
    struct my_type_traits<int>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 unsigned int
    template <>
    struct my_type_traits<unsigned int>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 long
    template <>
    struct my_type_traits<long>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 unsigned long
    template <>
    struct my_type_traits<unsigned long>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 float
    template <>
    struct my_type_traits<float>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 double
    template <>
    struct my_type_traits<double>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };
    // 模板偏特化，针对特定的型别 long double
    template <>
    struct my_type_traits<long double>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        typedef __my_true_type _has_trivial_destructor;
        typedef __my_true_type _is_POD_type;
    };

#if 1
    /*

    对于用户自己定义的类型，需要增加模板偏特化，如下：

    */
    class A
    {
    public:
        A(){};
        // To do
    };
    // 模板偏特化，针对用户定义的类型，自定义是__my_true_type或者__my_false_type
    template <>
    struct my_type_traits<A>
    {
        typedef __my_true_type _has_trivial_default_constructor;
        typedef __my_true_type _has_trivial_copy_constructor;
        typedef __my_true_type _has_trivial_assignment_operator;
        // typedef __my_true_type _has_trivial_destructor;
        typedef __my_false_type _has_trivial_destructor;
        typedef __my_false_type _is_POD_type;
        // typedef __my_true_type _is_POD_type;
    };
#endif
} // namespace mySTL

#endif // __MY_TYPE_TRAITS_H__