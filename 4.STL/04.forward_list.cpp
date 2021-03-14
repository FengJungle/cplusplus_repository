#include <iostream>
#include <string>
#include <forward_list>
using namespace std;

void print(forward_list<string> &ls)
{
    forward_list<string>::const_iterator ite;
    for (ite = ls.begin(); ite != ls.end(); ite++)
    {
        cout << *ite << "\t";
    }
    cout << endl;
}

void test1()
{
    forward_list<string>fls{"Good", "Bad", "Excellent", "Beautiful","Ugly"};
    print(fls);

    // Wrong, forward_list没有size()方法
    // cout<<"forward_list.size():\t"<<fls.size()<<endl;

    cout<<"forward_list.max_size():\t"<<fls.max_size()<<endl;

    cout << "forward_list.front():\t" << fls.front() << endl;

    // Wrong, forward_list没有back()方法，只能访问一端
    // cout << "forward_list.back():\t" << fls.back() << endl;

    // 从头部插入
    fls.push_front("Hello");
    print(fls);

    // Wrong, forward_list没有push_back()方法，只能从一端插入
    // fls.push_back("Goodix");


    // 排序
    fls.sort();
    print(fls);
}

int main()
{

    test1();
}