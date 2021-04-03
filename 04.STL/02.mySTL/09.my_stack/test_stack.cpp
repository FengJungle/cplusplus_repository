#include <iostream>
#include "my_stack.h"
using namespace std;
using namespace mySTL;

template<typename T>
void printStack(my_stack<T>& s)
{
    for(int i=0;i<s.size();i++)
    {
        cout<<s[i]<<" ";
    }
    cout<<endl;
}

void test_stack()
{
    my_stack<int> s1;
    s1.push(11);
    s1.push(2);
    s1.push(31);
    s1.push(56);
    s1.push(876);
    cout << s1.size() << endl;
    printStack(s1);
    cout << s1.top() << endl;
    s1.pop();
    printStack(s1);
    cout << s1.size() << endl;
}

int main(int argc, char *argv[])
{
    test_stack();

    return 0;
}