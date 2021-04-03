#ifndef _MY_ARRAY_H_
#define _MY_ARRAY_H_

/*

File Name:   my_array.h
Description: array
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "../01.my_typetraits/my_typetraits.h"
#include "../02.my_iteratortraits/my_iteratortraits.h"
#include "../03.my_alloc/uninitialized.h"
#include "my_array_iterator.h"

namespace mySTL
{
    template <typename T, size_t Size>
    class my_array
    {
    public:
        typedef T _value_type;
        typedef ptrdiff_t _difference_type;
        typedef T *_pointer;
        typedef T &_reference;
        typedef const T *_const_pointer;
        typedef const T &_const_reference;

        typedef my_array_iterator<T, Size> iterator;

        // 默认构造函数
        my_array()
        {
            for (auto i = 0; i < Size; i++)
            {
                Element[i] = T();
            }
        }

        // 初始化列表构造
        my_array(initializer_list<T> il)
        {
            size_t j = 0;
            for (auto i = il.begin(); i != il.end(); i++)
            {
                this->Element[j++] = *i;
                if (j >= Size)
                {
                    break;
                }
            }
            if (Size > il.size())
            {
                for (auto i = il.size(); i < Size; i++)
                {
                    Element[i] = T();
                }
            }
        }

        // 拷贝构造
        my_array(const my_array &other)
        {
            for (size_t i = 0; i < Size; i++)
            {
                Element[i] = other.Element[i];
            }
        }

        // 拷贝赋值
        my_array &operator=(const my_array &other) const
        {
            if (*this != other)
            {
                for (size_t i = 0; i < Size; i++)
                {
                    this->Element[i] = other.Element[i];
                }
            }

            return *this;
        }

        size_t size() const
        {
            return Size;
        }

        size_t max_size() const
        {
            return Size;
        }

        bool empty() const
        {
            return Size == 0;
        }

        _reference at(size_t index)
        {
            assert(index >= 0 && index < Size);
            return Element[index];
        }

        _reference operator[](size_t index)
        {
            assert(index >= 0 && index < Size);
            return Element[index];
        }

        _reference front()
        {
            return Element[0];
        }

        _reference back()
        {
            return Element[Size - 1];
        }

        // 获取数组首地址
        const T *data() const
        {
            return Element;
        }

        iterator begin()
        {
            return iterator(Element, 0);
        }

        iterator end()
        {
            return iterator(Element, Size);
        }

    private:
        T Element[Size];
    };
} // namespace mySTL

#endif // _MY_ARRAY_H_