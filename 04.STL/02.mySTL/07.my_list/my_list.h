#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <new.h>

namespace mySTL
{

    // list的节点
    template <typename T>
    struct list_node
    {
        list_node(list_node *iprev = nullptr, list_node *inext = nullptr, T idata = T()) : prev(iprev), next(inext), data(idata)
        {
        }
        list_node *prev;
        list_node *next;
        T data;
    };

    // 迭代器
    template <typename T>
    class my_list_iterator
    {
    public:
        typedef my_list_iterator<T> iterator;

        list_node<T> *_node;

    public:
        my_list_iterator(list_node<T> *x) : _node(x)
        {
        }

        my_list_iterator()
        {
        }

        my_list_iterator(const iterator &x) : _node(x._node)
        {
        }
        
        iterator& operator=(const iterator& other)
        {
            if(*this != other)
            {
                _node = other._node;
            }
            return *this;
        }
        
        bool operator==(const iterator &other)
        {
            return _node == other._node;
        }

        bool operator!=(const iterator &other)
        {
            return _node != other._node;
        }

        T& operator*()
        {
            return (*_node).data;
        }

        T* operator->()
        {
            return &(_node->data);
        }

        iterator &operator++()
        {
            _node = (list_node<T> *)(_node->next);
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        iterator &operator--()
        {
            _node = (list_node<T> *)(_node->prev);
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
    };

    template<typename T>
    class my_list
    {
    private:
        list_node<T> *node;

    public:
        // 迭代器
        typedef my_list_iterator<T> iterator;

    public:
        my_list()
        {
            empty_initialize();
        }

        my_list(size_t n, const T& x)
        {
            empty_initialize();
            insert(begin(), n, x);
        }

        my_list(const initializer_list<T>il)
        {
            empty_initialize();
            for (int i = 0; i < il.size(); i++)
            {
                insert(end(), *(il.begin() + i));
            }
        }

    public:
        iterator begin()
        {
            return node->next;
        }

        iterator end()
        {
            return node;
        }

        bool empty() const
        {
            return node->next == node;
        }

        ptrdiff_t size()
        {
            ptrdiff_t ret = 0;
            iterator tmp = begin();
            for(;tmp != end();tmp++)
            {
                ret++;
            }
            return ret;
        }

        T& front()
        {
            return *begin();
        }

        T& back()
        {
            return *(--end());
        }

        void push_back(const T& x)
        {
            insert(end(), x);
        }

        void push_front(const T& x)
        {
            insert(begin(), x);
        }

        iterator insert(iterator position, const T& x)
        {
            // 返回新插入的节点所在的位置
            list_node<T>* p = create_node(x);
            p->next = position._node;
            p->prev = position._node->prev;
            (position._node->prev)->next = p;
            position._node->prev = p;
            return p;            
        }

        iterator insert(iterator position, size_t n, const T& x)
        {
            iterator ret = position;
            for (; 0 < n; --n)
            {
                insert(position, x);
            }
            return ret;
        }

        iterator insert(iterator position, iterator begin, iterator end)
        {
            iterator ret = position;
            for(;begin != end;++begin)
            {
                insert(position, *begin);
            }
            return ret;
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            erase(end());
        }
 
        iterator erase(iterator position)
        {
            list_node<T>* next = position._node->next;
            list_node<T>* prev = position._node->prev;
            prev->next = next;
            next->prev = prev;
            free_node(position._node);
            // 返回当前迭代器的下一个节点
            return iterator(next);
        }

        void clear()
        {
            list_node<T>* cur = node->next;
            while(cur != node)
            {
                list_node<T>* temp = cur;
                cur = cur->next;
                free_node(temp);
            }
            node->next = node->prev = node;
        }

        // 将li中的所有元素接合于position所指位置之前，il必须不同于*this
        void splice(iterator position, my_list<T>& li)
        {
            if(!li.empty())
            {
                transfer(position, li.begin(), li.end());
            }
        }

        // 将[first, last)内的元素接合于position所指位置之前。position和[first, last)可指向同一个list
        void splice(iterator position, iterator first, iterator last)
        {
            if(first != last)
            {
                transfer(position, first, last);
            }
        }

        // 将list逆向重置
        void reverse()
        {
            if (node->next == node          /* 链表为空 */
                || node->next->next == node /* 链表只有一个元素 */
            )
            {
                return;
            }
            iterator first = begin();
            ++first;
            while(first != end())
            {
                iterator old = first;
                ++first;
                transfer(begin(), old, first);
            }
        }

    protected:
        // 产生一个空的链表
        void empty_initialize()
        {
            node = get_node();
            node->next = node;
            node->prev = node;
        }
        
        // 将[first, last)内的所有元素移动到position之前
        void transfer(iterator postion, iterator first, iterator last)
        {
            if(postion != last)
            {
                list_node<T>* first_node = first._node;
                list_node<T>* last_node = last._node;
                list_node<T>* position_node = postion._node;

                last_node->prev->next = position_node;
                first_node->prev->next = last_node;
                position_node->prev->next = first_node;
                list_node<T>* tmp = postion._node->prev;
                position_node->prev = last_node->prev;
                last_node->prev = first_node->prev;
                first_node->prev = tmp;
            }
        }

    private:
        list_node<T>* create_node(const T& x)
        {
            list_node<T> *tmp = get_node();
            new (&(tmp->data)) T(x);
            return tmp;
        }

        // 分配一个节点，并返回
        list_node<T>* get_node()
        {
            return new list_node<T>();
        }

        // 释放一个节点
        void free_node(list_node<T>* p)
        {
            delete p;
            p = nullptr;
        }
    };
}

#endif // _MY_LIST_H_