#include <iostream>
#include <list>
using namespace std;

void print(list<string> &ls)
{
    list<string>::const_iterator ite;
    for (ite = ls.begin(); ite != ls.end(); ite++)
    {
        cout << *ite << "\t";
    }
    cout << endl;
}

void test1()
{
    list<string> ls1{"Good", "Bad", "Just so so"};
    list<string> ls2 = {"Today", "Tomorrow", "Yestoday"};
    list<string> ls3(10);
    list<string> ls4(10, "Chengdu");
    print(ls1);
    print(ls2);
    print(ls4);

    cout << "list.size():\t" << ls1.size() << endl;
    cout << "list.max_size():\t" << ls1.max_size() << endl;
    // cout<<"list.capacity():\t"<<ls1.capacity()<<endl; // Wrong, list没有capacity()方法
    cout << "list.front():\t" << ls1.front() << endl;
    cout << "list.back():\t" << ls1.back() << endl;
    // cout<<"list[2]:\t"<<ls1[2]<<endl; // Wrong, list不支持随机访问
}

/*

Test2: 插入 和 排序

*/
void test2()
{
    list<string> ls = {"Today", "Tomorrow", "Yestoday"};
    print(ls);

    // 尾部插入
    ls.push_back("Hello");
    print(ls);

    // 头部插入
    ls.push_front("Bye");
    print(ls);

    // 指定位置插入指定范围元素
    string arr[3] = {"Shenzhen", "Guangzhou", "Shanghai"};
    ls.insert(ls.begin(), arr, arr + 3);
    print(ls);

    // 指定位置插入2个"Beijing"
    auto ite = ls.insert(ls.begin(), 2, "Beijing");
    cout << "Here:" << *ite << endl;
    print(ls);

    // 指定位置插入“Wuhan"
    auto ite2 = ls.insert(ls.begin(), "Wuhan");
    print(ls);
    cout << "Here 2" << *ite2 << endl;

    // 排序
    ls.sort(); // list有自己的排序函数
    print(ls);
}

/*

Test3: 删除

*/
void test3()
{
    list<string> ls = {"Today", "Tomorrow", "Yestoday"};
    ls.push_back("Shanghai");
    ls.push_back("Wuhan");
    ls.push_back("Changsha");
    ls.erase(ls.end());
    print(ls);

    ls.pop_back();
    print(ls);

    ls.pop_front();
    print(ls);

    // ls.erase(ls.begin(), ls.begin()+2);
    cout << ls.size() << endl;

    ls.clear();
    print(ls);

    

}

int main()
{

    // test1();

    test2();

    // test3();

    return 0;
}