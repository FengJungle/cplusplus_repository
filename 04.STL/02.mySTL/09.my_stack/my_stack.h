#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include "../08.my_deque/my_deque.h"
namespace mySTL
{
    template <typename T, typename Sequence = my_deque<T>>
    class my_stack
    {
    protected:
        Sequence c;
        
        template <typename Type, typename SequenceType>
        friend bool operator==(const my_stack<Type, SequenceType> &s1, const my_stack<Type, SequenceType> &s2)
        {
            return s1.c == s2.c;
        }

        template <typename Type, typename SequenceType>
        friend bool operator<(const my_stack<Type, SequenceType> &s1, const my_stack<Type, SequenceType> &s2)
        {
            return s1.c < s2.c;
        }

    public:
        my_stack() : c()
        {
        }
    public:
        bool empty() const
        {
            return c.empty();
        }
        size_t size() const
        {
            return c.size();
        }
        T &top()
        {
            return c.back();
        }
        void push(const T &x)
        {
            c.push_back(x);
        }
        void pop()
        {
            c.pop_back();
        }
        T& operator[](size_t index)
        {
            return c[index];
        }
    };
} // namespace mySTL

#endif // _MY_STACK_H_