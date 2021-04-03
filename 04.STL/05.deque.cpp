#include <iostream>
#include <deque>
using namespace std;

void print(deque<int> &dq)
{
    deque<int>::const_iterator cite;
    for (cite = dq.begin(); cite != dq.end(); cite++)
    {
        cout << *cite << "\t";
    }
    cout << endl;
}

void test1()
{
    // 10个1
    deque<int> dqInt(10, 1);
    print(dqInt);
    // 10个默认初始化的int
    deque<int> dqInt2(10);
    print(dqInt2);
    deque<int> dqInt3 = {1, 2, 3, 4, 5, 6};
    deque<int> dqInt4{11, 22, 33, 44, 55, 66};
    deque<int> dqInt5 = dqInt4;
    deque<int> dqInt6(dqInt4);
    print(dqInt3);
    print(dqInt4);
    print(dqInt5);
    print(dqInt6);

    cout << "deque.size():\t" << dqInt4.size() << endl;
    cout << "deque.max_size():\t" << dqInt4.max_size() << endl;
    // cout<<"deque.capacity():\t"<<dqInt4.capacity()<<endl; // Wrong, deque没有capacity()方法

    cout << "deque.front():\t" << dqInt4.front() << endl;
    cout << "deque.back():\t" << dqInt4.back() << endl;
    cout << "deque[3]]:\t" << dqInt4[3] << endl;

    // 头部和尾部插入元素
    dqInt4.push_front(99);
    dqInt4.push_back(100);
    print(dqInt4);
    getchar();

    // 指定位置插入一个元素
    dqInt4.insert(dqInt4.begin() + 4, 200);
    print(dqInt4);
    getchar();

    // 指定位置插入3个333
    dqInt4.insert(dqInt4.begin(), 3, 333);
    print(dqInt4);
    getchar();

    // 指定位置插入指定范围的元素
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    dqInt4.insert(dqInt4.begin() + 5, arr, arr + 4);
    print(dqInt4);
    getchar();

    // 删除
    dqInt4.pop_front();
    dqInt4.pop_back();
    dqInt4.erase(dqInt4.begin(), dqInt4.begin() + 3);
    dqInt4.clear();
}

int main()
{
    test1();

    return 0;
}