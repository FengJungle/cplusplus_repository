#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

/*

File Name:   my_vector.h
Description: my_vector
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "../03.my_alloc/alloc.h"
#include "../03.my_alloc/alloc.cpp"
#include "../03.my_alloc/allocator.h"
#include "../03.my_alloc/construct.h"
#include "../03.my_alloc/uninitialized.h"

namespace mySTL
{
    template <typename T,
              typename Alloc = alloc>
    class my_vector
    {
    public:
        typedef T _value_type;
        typedef ptrdiff_t _difference_type;
        typedef T *_pointer;
        typedef T &_reference;
        typedef const T *_const_pointer;
        typedef const T &_const_reference;

        typedef _value_type *iterator;

        typedef my_allocator<T, Alloc> data_allocator;

    protected:
        // 表示目前使用的空间的头
        iterator start;
        // 表示目前使用的空间的尾
        iterator finish;
        // 表示目前可用空间的尾
        iterator end_of_storage;

        void insert_aux(iterator position, const T &x)
        {
            // 还有备用空间
            if (finish != end_of_storage)
            {
                // 开辟一个空间，并调整finish
                construct(finish, *(finish - 1));
                ++finish;
                T x_copy = x;
                // position~finish的元素依次往后复制：从最后一个元素开始复制直到第一个元素
                copy_backward(position, finish - 2, finish - 1);
                // position位置插入目标值
                *position = x_copy;
            }
            // 已无备用空间
            else
            {
                const size_t old_size = size();
                // 如果原大小为0，则配置为1，否则len配置为原大小的两倍
                const size_t len = old_size != 0 ? 2 * old_size : 1;

                iterator new_start = data_allocator::allocate(len);
                iterator new_finish = new_start;

                // 将原来vector的内容拷贝至新vector
                new_finish = uninitialized_copy(start, finish, new_start);
                construct(new_finish, x);
                ++new_finish;
                new_finish = uninitialized_copy(position, finish, new_finish);

                destroy(begin(), end());
                _deallocate();

                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }

        void _deallocate()
        {
            if (start)
            {
                data_allocator::deallocate(start, size_t(end_of_storage - start));
            }
        }

        void fill_initialize(size_t n, const T &value)
        {
            start = allocate_and_fill(n, value);
            finish = start + n;
            end_of_storage = finish;
        }

        iterator allocate_and_fill(size_t n, const T &value)
        {
            iterator result = data_allocator::allocate(n);
            uninitialized_fill_n(result, n, value);
            return result;
        }

    public:
        // 构造函数
        my_vector() : start(0), finish(0), end_of_storage(0)
        {
        }

        my_vector(size_t n, const T &value)
        {
            fill_initialize(n, value);
        }

        my_vector(int n, const T &value)
        {
            fill_initialize(n, value);
        }

        my_vector(long n, const T &value)
        {
            fill_initialize(n, value);
        }

        explicit my_vector(size_t n)
        {
            fill_initialize(n, T());
        }

        // 初始化列表构造
        my_vector(initializer_list<T> il)
        {
            start = data_allocator::allocate(il.size());
            finish = start;
            size_t j = 0;
            for (auto i = il.begin(); i != il.end(); i++)
            {
                *finish = *i;
                finish++;
            }
        }

        // 拷贝构造
        my_vector(const my_vector &other)
        {
            this->start = data_allocator::allocate(other.end_of_storage - other.start);
            this->finish = this->start + (other.finish - other.start);
            this->end_of_storage = other.end_of_storage - other.start;
            this->finish = uninitialized_copy(other.start, other.finish, this->start);
        }

        // 拷贝赋值
        my_vector &operator=(const my_vector &other)
        {
            if (*this != other)
            {
                destroy(start, finish);
                _deallocate();
                this->start = data_allocator::allocate(other.end_of_storage - other.start);
                this->finish = this->start + (other.finish - other.start);
                this->end_of_storage = other.end_of_storage - other.start;
                this->finish = uninitialized_copy(other.start, other.finish, this->start);
            }
            return (*this);
        }

        // 析构函数
        ~my_vector()
        {
            destroy(start, finish);
            _deallocate();
        }

    public:
        iterator begin()
        {
            return start;
        }

        iterator end()
        {
            return finish;
        }

        _difference_type size()
        {
            return (_difference_type(end()) - _difference_type(begin())) / sizeof(T);
        }

        _difference_type capacity()
        {
            return _difference_type(end_of_storage - start) / sizeof(T);
        }

        bool empty()
        {
            return begin() == end();
        }

        _reference operator[](size_t index)
        {
            return *(begin() + index);
        }

    public:
        _reference front()
        {
            return *begin();
        }

        _reference back()
        {
            return *(end() - 1);
        }

        void push_back(const T &val)
        {
            if (finish != end_of_storage)
            {
                construct(finish, val);
                finish++;
            }
            else
            {
                insert_aux(end(), val);
            }
        }

        void pop_back()
        {
            --finish;
            destroy(finish);
        }

        iterator erase(iterator position)
        {
            if (position + 1 != end())
            {
                copy(position + 1, finish, position);
            }
            --finish;
            destroy(finish);
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            iterator i = copy(last, finish, first);
            destroy(i, finish);
            finish = finish - (last - first);
            return first;
        }

        void resize(size_t new_size, const T &val)
        {
            if (new_size < size())
            {
                erase(begin() + new_size, finish);
            }
            else
            {
                insert(end(), new_size - size(), val);
            }
        }

        void resize(size_t new_size)
        {
            resize(new_size, T());
        }

        void clear()
        {
            erase(begin(), end());
        }

        void insert(iterator position, size_t n, const T &val)
        {
            if (n != 0)
            {
                // 剩余空间足够
                if (size_t(end_of_storage - finish) >= n)
                {
                    T val_copy = val;
                    // 插入点之后，现有的元素个数
                    const size_t elems_after = finish - position;
                    iterator old_finish = finish;

                    // 插入点之后的现有元素个数 大于 即将插入的元素个数
                    if (elems_after > n)
                    {
                        // a. 先将finish-n ~ finish的元素后移
                        uninitialized_copy(finish - n, finish, finish);
                        finish += n;
                        // b. 再把position~old_finish的元素从尾到头放到old_finish往前的位置
                        copy_backward(position, old_finish - n, old_finish);
                        // c. 最后从position开始填入待插入的元素
                        fill(position, position + n, val_copy);
                    }
                    // 插入点之后的现有元素个数 小于等于 即将插入的元素个数
                    else
                    {
                        // a. 先在finish后面填充(n-elems_after)个待插入元素
                        uninitialized_fill_n(finish, n - elems_after, val_copy);
                        // b. finish标记往后移动（n-elems_after)
                        finish += n - elems_after;
                        // c. 将(position, old_finish)的元素放到finish后面，至此，原始的元素移动完成
                        uninitialized_copy(position, old_finish, finish);
                        // d. 调整finish标记
                        finish += elems_after;
                        // e. 第a个步骤只插入了n-elems_after个元素，现在将剩余的元素插入完成
                        fill(position, old_finish, val_copy);
                    }
                }
                // 剩余空间不够
                else
                {
                    const size_t old_size = size();
                    const size_t len = old_size + old_size > n ? old_size : n;

                    // 配置新空间
                    iterator new_start = data_allocator::allocate(len);
                    iterator new_finish = new_start;

                    // a. 将旧vector的插入点之前的元素复制到新vector
                    new_finish = uninitialized_copy(start, position, new_start);
                    // b. 将新增元素加入到新vector
                    new_finish = uninitialized_fill_n(new_finish, n, val);
                    // c. 将旧vecotr插入点之后的元素加入到新vector
                    new_finish = uninitialized_copy(position, finish, new_finish);

                    // 清除并释放旧的vector
                    destroy(start, finish);
                    _deallocate();

                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start + len;
                }
            }
        }
    };
} // namespace mySTL

#endif // _MY_VECTOR_H_
