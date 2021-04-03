#ifndef _MY_PTR_BASE_H_
#define _MY_PTR_BASE_H_

#include "my_ref_count.h"

namespace mySTL
{
    // 前向声明
    template<typename T>
    class my_weak_ptr;

    template<typename T>
    class my_shared_ptr;

    template <typename T>
    class my_ptr_base
    {
    public:
        // 默认析构函数
        ~my_ptr_base() = default;

        // 返回保存的指针
        T *get() const
        {
            return ptr;
        }

        // 返回引用计数
        long use_count() const
        {
            return pRef ? pRef->use_count() : 0;
        }

        void swap(my_ptr_base& other)
        {
            
        }

    private:
        my_ref_count *pRef{nullptr};
        T *ptr{nullptr};
    };
}


#endif // _MY_PTR_BASE_H_