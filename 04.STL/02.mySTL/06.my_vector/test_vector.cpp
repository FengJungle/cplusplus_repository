#include <iostream>
using namespace std;

/*

File Name:   test_vector.h
Description: 测试my_vector
Date:        2020/12/06
Author:      Feng Qiangguo

*/

#include "my_vector.h"

using namespace mySTL;

#include<vector>

class Tmp
{
private:
    int a;

public:
    Tmp(int ia = 0) : a(ia)
    {
    }
    friend ostream &operator<<(ostream &os, const Tmp &t);
};
ostream &operator<<(ostream &os, const Tmp &t)
{
    os << t.a;
    return os;
}

void test_vector()
{
    
    my_vector<int>a{1,2,3,4};
    a.insert(a.begin(), 3, 33);
    a.insert(a.end(), 2, 99);

    cout << "size()" << a.size() << endl;

    my_vector<int>::iterator ite = a.begin();
    for(ite;ite != a.end();ite++)
    {
        cout << *ite << " ";
    }
    cout << endl;

    a.erase(a.begin(), a.begin() + 4);
    ite = a.begin();
    for(ite;ite != a.end();ite++)
    {
        cout << *ite << " ";
    }

    cout << "\n++++++++++++++++++++++" << endl;
    my_vector<Tmp> b;
    b.push_back(Tmp(5));
    b.push_back(Tmp(50));
    b.push_back(Tmp(500));
    cout << b.size() << endl;
    cout << b.back() << endl;
    b.pop_back();
    cout << b.back() << endl;
    cout << b.front() << endl;

    cout << "++++++++++++++++++++++" << endl;

}

void testStlVetor()
{
    vector<int> a(10, 1);
    for(int i=0;i<10;i++)
    {
        a[i] = i + 1;
    }
    a.insert(a.begin()+4, 3, 0);
    for(int i=0;i<a.size();i++)
    {
        cout<<a[i]<<" ";
    }

    cout << endl;
}

int main(int argc, char* argv[])
{
    // test_vector();

    testStlVetor();

    return 0;
}