#ifndef _MY_ARRAY_ITERATOR_H_
#define _MY_ARRAY_ITERATOR_H_

/*

File Name:   my_array_iterator.h
Description: array的迭代器
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "../02.my_iteratortraits/my_iteratortraits.h"
#include "assert.h"

namespace mySTL
{
    template <typename T, size_t Size>
    class my_array_iterator : public my_iterator<my_random_access_iterator_tag, T>
    {
    public:
        typedef my_random_access_iterator_tag _iterator_category;
        typedef T _value_type;
        typedef const T *_pointer;
        typedef const T &_reference;
        typedef ptrdiff_t _difference_type;

        my_array_iterator() : ptr(0), index(0)
        {
        }
        my_array_iterator(_pointer p, size_t offset = 0) : ptr(p), index(offset)
        {
        }
        _pointer operator->()
        {
            return ptr + index;
        }
        _reference operator*()
        {
            return (*operator->());
        }
        _reference operator[](size_t _index) const
        {
            return *(*this + _index);
        }
        my_array_iterator &operator++()
        {
            assert(index < Size);
            ++index;
            return *this;
        }
        my_array_iterator operator++(int)
        {
            assert(index < Size);
            my_array_iterator tmp = *this;
            ++*this;
            return tmp;
        }
        my_array_iterator &operator--()
        {
            assert(index != 0);
            --index;
            return *this;
        }
        my_array_iterator operator--(int)
        {
            my_array_iterator tmp = *this;
            --*this;
            return tmp;
        }
        my_array_iterator &operator+=(const ptrdiff_t off)
        {
            assert(index < Size && index + off < Size);
            index += off;
            return *this;
        }
        my_array_iterator &operator+(const ptrdiff_t off) const
        {
            my_array_iterator tmp = *this;
            return tmp += off;
        }
        my_array_iterator &operator-=(const ptrdiff_t off)
        {
            assert(index >= 0 && index - off >= 0);
            index -= off;
            return *this;
        }
        my_array_iterator &operator-(const ptrdiff_t off) const
        {
            my_array_iterator tmp = *this;
            return tmp -= off;
        }
        ptrdiff_t operator-(const my_array_iterator &right)
        {
            return static_cast<ptrdiff_t>(index - right.index);
        }
        bool operator==(const my_array_iterator &right) const
        {
            return this->index == right.index;
        }
        bool operator!=(const my_array_iterator &right) const
        {
            return !(*this == right);
        }
        bool operator<(const my_array_iterator &right) const
        {
            return this->index < right.index;
        }
        bool operator>(const my_array_iterator &right) const
        {
            return right < *this;
        }
        bool operator<=(const my_array_iterator &right) const
        {
            return !(right > *this);
        }
        bool operator>=(const my_array_iterator &right) const
        {
            return !(*this < right);
        }

    private:
        // 指向array的起始处
        _pointer ptr;
        // 当前偏移
        size_t index;
    };
} // namespace mySTL

#endif // _MY_ARRAY_ITERATOR_H_
