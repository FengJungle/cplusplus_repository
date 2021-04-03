#ifndef _MY_DEQUE_H_
#define _MY_DEQUE_H_

#include "my_deque_iterator.h"
#include <new.h>

namespace mySTL
{
    template <typename T, size_t BufSiz = 0>
    class my_deque
    {
    public:
        // 迭代器
        typedef my_deque_iterator<T, BufSiz> iterator;
        typedef T **map_pointer;

    protected:
        // 第一个node
        iterator start;
        // 最后一个node
        iterator finish;

        // 指向map， map可增长，是一个vector
        map_pointer map;
        // map内有多少个指针
        size_t map_size;

    private:
        size_t buffer_size()
        {
            return iterator().buffer_size();
        }

        // 产生并安排好deque的结构
        void create_map_nodes(int n)
        {
            // 需要的节点数量 = （元素个数/每个缓冲区大小)+1，如果刚好整除，会多配置一个节点
            size_t num_nodes = n / buffer_size() + 1;

            // 一个map管理的节点数量：最少8个，最多是所需节点数量+2（前后各预留一个，扩充用）
            map_size = 8 > (num_nodes + 2) ? 8 : (num_nodes + 2);
            map = new T*[map_size];

            // 使nstart和nfinish指向map所有节点的中部区段，保持在最中央，两边扩充能量一样大
            map_pointer nstart = map + (map_size - num_nodes) / 2;
            map_pointer nfinish = nstart + num_nodes - 1;

            // 为map内的每个现用节点配置缓冲区
            map_pointer cur;
            for (cur = nstart; cur <= nfinish; ++cur)
            {
                *cur = new T[buffer_size()];
            }

            // 调整节点
            this->start.set_node(nstart);
            this->finish.set_node(nfinish);
            this->start.cur = start.first;
            this->finish.cur = this->finish.first + n % buffer_size();
        }

        void fill_initialize(int n, const T& value)
        {
            create_map_nodes(n);
            map_pointer cur;
            for (cur = start.node; cur < finish.node; ++cur)
            {
                for (int i = 0; i < buffer_size(); i++)
                {
                    (*cur)[i] = value;
                }
            }
            cur = finish.node;
            for (int i = 0; i <= (finish.cur - finish.first); i++)
            {
                (*cur)[i] = value;
            }
        }

        void reallocate_map(size_t nodes_to_add, bool add_at_front)
        {
            size_t old_num_nodes = finish.node - start.node + 1;
            size_t new_num_nodes = old_num_nodes + nodes_to_add;

            map_pointer new_nstart;
            if (map_size > 2 * new_num_nodes)
            {
				new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
                if (new_nstart < start.node)
                {
                    copy(start.node, finish.node + 1, new_nstart);
                }
                else
                {
                    copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
                }
            }
            else
            {
				size_t new_map_size = map_size + (map_size > nodes_to_add ? map_size : nodes_to_add) + 2;
                // 配置一块新空间给新map使用
                map_pointer new_map = new T*[new_map_size];
                new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);

                // 把map内容拷贝过来
                copy(start.node, finish.node + 1, new_nstart);

                // 释放原map
                delete map;

                map = new_map;
                map_size = new_map_size;
            }
            start.set_node(new_nstart);
            finish.set_node(new_nstart + old_num_nodes - 1);
        }

        void reserve_map_at_front(size_t nodes_to_add = 1)
        {
            // map前端的节点的备用空间不足，需要重新换一个更大的map
            if (nodes_to_add > (start.node - map))
            {
                reallocate_map(nodes_to_add, true);
            }
        }

        void reserve_map_at_back(size_t nodes_to_add = 1)
        {
            // map尾端的节点的备用空间不足，需要重新换一个更大的map
            if (nodes_to_add + 1 > map_size - (finish.node - map))
            {
                reallocate_map(nodes_to_add, false);
            }
        }

        void push_back_aux(const T& value)
        {
            reserve_map_at_back();
            *(finish.node + 1) = new T[buffer_size()];

            *finish.cur = value;
            finish.set_node(finish.node + 1);
            finish.cur = finish.first;
        }

        void push_front_aux(const T& value)
        {
            reserve_map_at_front();
            *(start.node-1) = new T[buffer_size()];

            start.set_node(start.node - 1);
            start.cur = start.last - 1;
            new(start.cur) T(value);
        }

        void pop_back_aux()
        {
            delete finish.first;
            map_pointer tmp = finish.node;
            finish.set_node(finish.node - 1);
            finish.cur = finish.last - 1;
            delete tmp;
        }

        void pop_front_aux()
        {
            delete start.cur;
            map_pointer tmp = start.node;
            start.set_node(start.node+1);
            start.cur = start.first;
            delete tmp;
        }
    public:
        my_deque(int n, const T& value):start(), finish(), map(0), map_size(0)
        {
            fill_initialize(n, value);
        }

    public:
        void push_back(const T& value)
        {
            // 最后的缓冲区还有两个及以上的空间，则直接在备用空间上构造元素
            if(finish.cur != finish.last- 1)
            {
                new (finish.cur) T(value);
                ++finish.cur;
            }
            else // 尾部只剩一个空间，需要先配置一块新空间，再设置新元素
            {
                push_back_aux(value);
            }
        }

        void push_front(const T& value)
        {
            if(start.cur != start.first)
            {
                new (start.cur - 1) T(value);
                --start.cur;
            }
            else
            {
                push_front_aux(value);
            }
            
        }

        void pop_back()
        {
            if(finish.cur != finish.first)
            {
                --finish.cur;
                delete(finish.cur);
            }
            else
            {
                pop_back_aux();
            }
        }

        void pop_front()
        {
            if (start.cur != start.last - 1)
            {
                delete start.cur;
                ++start.cur;
            }
            else
            {
                pop_front_aux();
            }
        }
    public:
        /***********************************************************/
        iterator begin()
        {
            return start;
        }

        iterator end()
        {
            return finish;
        }

        T& operator[](size_t n)
        {
            return start[ptrdiff_t(n)];
        }

        T& front()
        {
            return *start;
        }

        T& back()
        {
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }

        size_t size() const
        {
            // 调用迭代器的operator-
            return finish - start;
        }

        bool empty() const
        {
            // 调用迭代器的operator==
            return finish == start;
        }
        /***********************************************************/
    };
} // namespace mySTL

#endif // _MY_DEQUE_H_