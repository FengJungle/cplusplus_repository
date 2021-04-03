#ifndef _REF_COUNT_BASE_H_
#define _REF_COUNT_BASE_H_

/*

File Name:   my_ref_count.h
Description: 引用计数类
Date:        2020/12/05
Author:      Feng Qiangguo

*/

namespace mySTL
{
    /*
    *
    * 引用计数类的基类
    * 
    */
    class my_ref_count_base
    {
    private:
        // Virtual, 由子类实现
        virtual void destroy() = 0;
        virtual void delete_this() = 0;

        unsigned long uses;
        unsigned long weaks;

    protected:
        // Constructor
        my_ref_count_base() : uses(1), weaks(1)
        {
        }

    public:
        // Virtual destructor
        virtual ~my_ref_count_base()
        {
        }
        
        // 引用计数+1
        void incref()
        {
            uses++;
        }

        // 引用计数-1，如果为0，则销毁对象
        void decref()
        {
            --uses;
            if (uses == 0)
            {
                destroy();
                decwref();
            }
        }

        void decwref()
        {
            --weaks;
            if (weaks == 0)
            {
                delete_this();
            }
        }

        // 返回引用计数
        long use_count() const
        {
            return uses;
        }
    };

    template <typename T>
    class my_ref_count : public my_ref_count_base
    {
    private:
        T *_Ptr;

    public:
        explicit my_ref_count(T *_Px) : my_ref_count_base(), _Ptr(_Px)
        {
        }

        virtual void destroy()
        {
            delete _Ptr;
        }

        virtual void delete_this()
        {
            /* Suicide, 自杀行为前提
            *  Ref: https://isocpp.org/wiki/faq/freestore-mgmt#delete-this
            * 
            * 100% 确保”this”对象是通过new分配的（不是通过new[]，不是placement new，不是栈上的局部对象，不是全局对象，不是另一个对象的数据成员；仅仅只是通过原始的new运算符）
            * 100% 确保调用”delete this”操作的成员函数是最后调用的成员函数
            * 100% 确保在当前函数中”delete this”后，调用的其他成员函数不会读取”this”对象。
            * 100% 再也不会使用”this”指针。即使你使用this指针和其他指针比较，例如nullptr，打印this指针，转换this指针等等。
            *
            */
            delete this;
        }
    };
} // namespace mySTL

#endif // _REF_COUNT_BASE_H_