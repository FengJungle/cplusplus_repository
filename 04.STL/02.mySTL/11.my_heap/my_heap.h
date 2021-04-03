#ifndef _MY_HEAP_H_
#define _MY_HEAP_H_

/*
*
* 1.二叉堆是一种完全二叉树，堆不是STL的容器组件，但它是优先队列的底层机制
* 2.根据元素的排列方式，分为最大堆和最小堆，最大堆每个节点的键值都大于等于其子节点的键值
* 3.由于堆是一颗完全二叉树，所以其底层可以用数组实现。为了满足堆支持动态变化的特性，底层应该使用vector。
*
*/

using namespace std;
#include <algorithm>
#include <vector>

namespace mySTL
{
    template <typename Type>
    class my_max_heap
    {
    private:
        vector<Type> data;
        int count;

    private:

        void swap(Type& a, Type& b)
        {
            Type tmp = a;
            a = b;
            b = tmp;
        }
        void shiftDown(int k)
        {
            // 当前孩子有孩子，就一定有左孩子（完全二叉树）
            while (k * 2 <= count)
            {
                int j = k * 2;
                if (j + 1 <= count && data[j + 1] > data[j])
                {
                    ++j;
                }
                if (data[k] >= data[j])
                {
                    break;
                }
                swap(data[j], data[k]);
                k = j;
            }
        }

        void shiftUp(int k)
        {
            while (k > 1 && data[k / 2] < data[k])
            {
                swap(data[k], data[k / 2]);
                k /= 2;
            }
        }

    public:
        // 构造函数, 构造一个空堆, 可容纳capacity个元素(数组元素的索引从1开始)
        my_max_heap() : data(1, Type()), count(0)
        {

        }

        my_max_heap(Type arr[], int n):data(1,Type()), count(0)
        {
            for(int i=0;i<n;i++)
            {
                push_heap(arr[i]);
            }
        }

        ~my_max_heap()
        {
            
        }

        // 插入元素
        void push_heap(Type val)
        {
            if(data.empty())
            {
                data.push_back(0);
            }
            if (count + 1 + 1 <= data.size())
            {
                data[count + 1] = val;
            }
            else
            {
                data.push_back(val);
            }
            count++;
            shiftUp(count);
        }

        // 弹出堆中的最值
        void pop_heap()
        {
            swap(data[1], data[size()]);
            //data.erase(data.end()-1);
            count--;
            shiftDown(1);
        }

        Type getMax()
        {
            Type ret = data[1];
        
            return ret;
        }

        int size()
        {
            return count;
        }

        bool empty()
        {
            return data.empty();
        }

        int capacity()
        {
            return data.capacity();
        }
    };
} // namespace mySTL

#endif // _MY_HEAP_H_