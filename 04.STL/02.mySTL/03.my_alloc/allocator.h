#ifndef _MY_ALLOCATOR_H_
#define _MY_ALLOCATOR_H_

/*

File Name:   allocator.h
Description: my_allocator
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "alloc.h"
#include "construct.h"

namespace mySTL
{
    template <typename T, typename Alloc>
    class my_allocator
    {
    public:
        static T *allocate(size_t n)
        {
            return 0 == n ? 0 : (T *)Alloc::allocate(n * sizeof(T));
        }
        static T *allocate(void)
        {
            return (T *)Alloc::allocate(sizeof(T));
        }
        static void deallocate(T *p, size_t n)
        {
            if (n != 0)
            {
                Alloc::deallocate(p, n * sizeof(T));
            }
        }
        static void deallocate(T *p)
        {
            Alloc::deallocate(p, sizeof(T));
        }

    private:
    };

} // namespace mySTL

#endif // _MY_ALLOCATOR_H_