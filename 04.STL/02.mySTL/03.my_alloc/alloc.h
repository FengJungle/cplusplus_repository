#ifndef _ALLOC_H_
#define _ALLOC_H_

/*

File Name:   alloc.h
Description: alloc, dealloc
Date:        2020/12/02
Author:      Feng Qiangguo

*/

#include <cstddef> //定义size_t

namespace mySTL
{
    class alloc
    {
    private:
        // 小型区块的上调边界
        enum{__ALIGN = 8};
        // 小型区块的上限
        enum{__MAX_BYTES = 128};
        // free-lists个数
        enum{__FREELISTS = __MAX_BYTES / __ALIGN};

        // free-lists的节点构造
        union obj
        {
            union obj *next;
            // The client see this
            char client_data[1];
        };

        // 16个free-lists
        static obj* free_list[__FREELISTS];

        // Chunk allocation state
        // 内存池起始位置
        static char* start_free;
        // 内存池结束为止
        static char* end_free;
        static size_t heap_size;

        // 将bytes调整为8的倍数
        static size_t ROUND_UP(size_t bytes)
        {
            return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
        }

        // 根据区块大小决定使用第几号free-list
        static size_t FREELIST_INDEX(size_t bytes)
        {
            return ((bytes + __ALIGN - 1) / __ALIGN - 1);
        }

        // 内部：返回大小为n的对象，并可能加入大小为n的其他区块到freelist
        static void *_refill(size_t n);

        // 内部：配置一大块空间，可容纳nobjs个大小为size的区块
        //      如果配置nobjs个区块受限制，nobjs会根据实际情况降低
        static char *_chunk_alloc(size_t size, int &nobjs); // 注意nobjs是引用

    public:
        static void *allocate(size_t n);
        static void deallocate(void *p, size_t n);
        static void *reallocate(void *p, size_t old_sz, size_t new_sz);

        // For debug
        static void printMemoryInfo();
    };
} // namespace mySTL

#endif // _ALLOC_H_