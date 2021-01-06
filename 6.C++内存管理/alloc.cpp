/*

File Name:   alloc.cpp
Description: alloc, dealloc
Date:        2020/12/03
Author:      Feng Qiangguo

*/

#include "alloc.h"
#include <cstdlib>
#include <iostream>

namespace mySTL
{
    char *alloc::start_free = 0;
    char *alloc::end_free = 0;
    size_t alloc::heap_size = 0;

    alloc::obj *alloc::free_list[__FREELISTS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 标准配置器接口allocate
    void *alloc::allocate(size_t n)
    {
        obj **my_free_list;
        obj *result;

        // 大于128字节就调用第一级配置器
        if (n > (size_t)__MAX_BYTES)
        {
            return malloc(n);
        }
        
        // 寻找合适的free list
        my_free_list = free_list + FREELIST_INDEX(n);
        result = *my_free_list;
        if (result == 0)
        {
            // 没找到可用的freelist，准备重新填充free list
            void *r = _refill(ROUND_UP(n));
            return r;
        }

        // 分配到的空间将从freelist中取出给用户使用
        *my_free_list = result->next;
        return result;
    }

    // 从内存池中取出新的空间，填入freelist
    // 内存池是由chunk_alloc配置完成
    void *alloc::_refill(size_t n)
    {
        // 默认取得20个新节点，如果内存池空间不足，则节点数量少于20个
        int nobjs = 20;

        // 调用chunk_alloc()尝试获取nobj个区块作为freelist的新节点
        char *chunk = _chunk_alloc(n, nobjs); // 注意nobjs传参是引用，该值可能会被修改
        
        obj **my_free_list;
        // result用于返回给客户端使用
        obj *result;
        // current_obj和next_obj用于链接freelist的新区块
        obj *current_obj;
        obj *next_obj;
        int i = 0;

        // 如果只取得1个新区块，将该区块分配给用户使用，freelist不会增加新节点
        if (1 == nobjs)
        {
            return chunk;
        }

        // 如果取得多于1个新区块，则准备加入freelist
        // 定位到对应的freelist
        my_free_list = free_list + FREELIST_INDEX(n);

        // result用于返回给客户端使用 在chunk空间里建立freelist
        result = (obj *)chunk;

        // 在freelist里串接新区块
        *my_free_list = next_obj = (obj *)(chunk + n);
        for (i = 1;; i++)
        {
            current_obj = next_obj;
            next_obj = (obj *)((char *)next_obj + n);
            if (nobjs - 1 == i) // 申请配置nobjs个新区块，因为要返回给用户一块，故最多在freelist里链接(nobjs-1)块
            {
                next_obj->next = 0;
                break;
            }
            else
            {
                current_obj->next = next_obj;
            }
        }

        return result;
    }

    /* 
    * Func       : _chunk_alloc
    * Description: 从内存池申请内存
    * Parameter  : size  - 将要申请的内存大小，已调整至8的倍数
    *              nobjs - 将要申请的新区块数量，这里是pass by reference，nobjs的值可能会被调整
    * return     : char* 
    */
    char *alloc::_chunk_alloc(size_t size, int &nobjs)
    {
        // 返回result
        char *result;

        // 总共需要申请的空间
        size_t total_bytes = size * nobjs;
        // 内存池剩余空间
        size_t bytes_left = end_free - start_free;

        // 1. 内存池剩余空闲空间完全够用，直接分配并返回
        if (bytes_left >= total_bytes)
        {
            result = start_free;
            // 内存池空闲内存开始指针往后移动，重新标记
            start_free += total_bytes;
            return result;
        }
        // 2. 内存池剩余空闲空间不够分配要求的那么多，但还能至少分配1个区块，调整真实分配的区块数量，并返回
        else if (bytes_left >= size)
        {
            nobjs = bytes_left / size;
            result = start_free;
            start_free += nobjs * size;
            return result;
        }
        // 3. 内存池剩余空闲空间不够分配1个新区块
        else
        {
            // 向堆申请的内存大小 = 需要申请内存大小的2倍 + 额外配置
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);

            // 检测当前内存池中是否还有残余的零头有利用价值
            if (bytes_left > 0)
            {
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free;
            }

            // 配置heap空间，补充内存池
            start_free = (char *)malloc(bytes_left);
            // heap空间不够，malloc失败
            if (0 == start_free)
            {
                int i;
                obj **my_free_list;
                obj *p;

                // 搜寻已有尚未使用的足够大小的区块：至少满足一个size
                for (i = size; i <= __MAX_BYTES; i += __ALIGN)
                {
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    // freelist内尚有未使用的区块
                    if (0 != p)
                    {
                        // 调整my_free_list
                        *my_free_list = p->next;
                        // 调整start_free, end_free
                        start_free = (char *)p;
                        end_free = start_free + i;

                        // 递归调用自己，为修正nobjs
                        return _chunk_alloc(size, nobjs);
                    }
                }
            }
            // 行至此处，heap里不剩余一点内存,调用一级配置器
            end_free = 0;
            start_free = (char *)malloc(bytes_to_get);
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            // 递归调用自己，为修正nobjs
            return _chunk_alloc(size, nobjs);
        }
    }

    // 空间释放函数
    void alloc::deallocate(void *p, size_t n)
    {
        obj *q = (obj *)p;
        obj **my_free_list;

        // n大于128就调用第一级配置器
        if (n > (size_t)__MAX_BYTES)
        {
            free(p);
            return;
        }

        // 确定对应的freelist
        my_free_list = free_list + FREELIST_INDEX(n);
        // 调整freelist，回收区块，将释放的空间加入freelist对应区块
        q->next = *my_free_list;
        *my_free_list = q;
    }

    void *alloc::reallocate(void *p, size_t old_sz, size_t new_sz)
    {
        deallocate(p, old_sz);
        return allocate(new_sz);
    }

    void alloc::printMemoryInfo()
    {
        std::cout << "Heap size: " << heap_size << std::endl;
        std::cout << "Start_free: " << end_free - start_free << std::endl;
        // std::cout << "End_free: " << *end_free << std::endl;
    }
} // namespace mySTL