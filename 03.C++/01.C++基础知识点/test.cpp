#include <stdio.h>
#include <iostream>
using namespace std;

#include <initializer_list>
#include <algorithm>
#include <vector>

void print(vector<int> &nums)
{
    for(auto i:nums)
    {
        cout<<i<<"  ";
    }
    cout<<endl;
}

bool cmp(int a, int b)
{
    return a>b;
}

int main()
{
    vector<int> num{1, 223, 23, 321, 115, 86};
    int Min = 50;
    int Max = 200;
    // 隐式捕获，值捕获方式
    auto tmp = find_if(num.begin(), num.end(), [=](int a){
        return a >= Min && a <= Max;
    });
    cout << *tmp++ << endl; // 输出115
    cout << *tmp << endl;   // 输出86

    return 0;
}
