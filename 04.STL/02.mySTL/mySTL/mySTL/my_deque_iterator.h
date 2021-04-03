#ifndef _MY_DEQUE_ITERATOR_H_
#define _MY_DEQUE_ITERATOR_H_

namespace mySTL
{
    template <typename T, size_t BufferSize>
    class my_deque_iterator
    {
    public:
        typedef T **map_pointer;
        typedef my_deque_iterator iterator;

        // 此迭代器所指的缓冲区中的现行元素
        T *cur;
        // 此迭代器所指的缓冲区中的头
        T *first;
        // 此迭代器所指的缓冲区中的尾
        T *last;
        // 指向管控中心
        map_pointer node;

    public:
        my_deque_iterator():cur(nullptr), first(nullptr), last(nullptr), node(nullptr)
        {
            
        }

        /*
        * 指定每个buffer的大小
        * ： 如果n != 0， 则buffer大小为客户指定的n
        * ： 否则，buffer的大小为默认值 512/sz 或 1
        */
        static size_t __deque_buffer_size(size_t n, size_t sz)
        {
            if (0 != n)
            {
                return n;
            }
            if (sz < 512)
            {
                return size_t(512 / sz);
            }
            return size_t(1);
        }

        /*
        * 获取buffer的大小
        */
        static size_t buffer_size()
        {
            // BufferSize是客户传入的大小，如果客户未指定，则为默认值0
            return __deque_buffer_size(BufferSize, sizeof(T));
        }

        /*
        * 调整当前node指向的缓冲区，并更新first、last指针
        */
        void set_node(map_pointer new_node)
        {
            this->node = new_node;
            this->first = *new_node;
            this->last = this->first + ptrdiff_t(buffer_size());
        }

        /*
        * 迭代器相减
        */
        ptrdiff_t operator-(const iterator &x) const
        {
            return ptrdiff_t(this->node - x.node - 1) * buffer_size() + (this->cur - this->first) + (x.last - x.cur);
        }

        iterator &operator++()
        {
            ++cur;
            // 判断当前缓冲区是否已经到达尾端，如果是，则跳到下一个缓冲区，并把cur指针指向下一个缓冲区的头
            if (cur == last)
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator ret = *this;
            ++*this;
            return ret;
        }

        iterator &operator--()
        {
            if (cur == first)
            {
                set_node(node - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        iterator operator--(int)
        {
            iterator ret = *this;
            --*this;
            return ret;
        }

        iterator &operator+=(ptrdiff_t n)
        {
            ptrdiff_t offset = cur - first + n;
            // 当前缓冲区剩余空间足够
            if (offset >= 0 && offset < ptrdiff_t(buffer_size()))
            {
                cur += n;
            }
            // 当前缓冲区剩余空间不够
            else
            {
                ptrdiff_t node_offset = offset > 0 ? offset / ptrdiff_t(buffer_size())
                                                   : -ptrdiff_t(-offset - 1) / buffer_size() - 1;
                set_node(node + node_offset);
                cur = first + (offset - node_offset * ptrdiff_t(buffer_size()));
            }
            return *this;
        }

        iterator operator+(ptrdiff_t n) const
        {
            iterator ret = *this;
            return ret += n;
        }

        iterator &operator-=(ptrdiff_t n)
        {
            return *this += (-n);
        }

        iterator operator-(ptrdiff_t n) const
        {
            iterator ret = *this;
            return ret -= n;
        }

        ptrdiff_t operator[](ptrdiff_t n) const
        {
            return *(*this + n);
        }

        bool operator==(const iterator &ite) const
        {
            return this->cur == ite.cur;
        }

        bool operator!=(const iterator &ite) const
        {
            return !(*this == ite);
        }

        bool operator<(const iterator &ite) const
        {
            return node == ite.node ? (cur < ite.cur) : (node < ite.node);
        }

        T& operator*()
        {
            return *cur;
        }

        T* operator->()
        {
            return &(operator*());
        }
    };
} // namespace mySTL

#endif // _MY_DEQUE_ITERATOR_H_