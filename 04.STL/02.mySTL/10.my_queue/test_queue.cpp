#include <iostream>
#include "my_queue.h"
using namespace std;
using namespace mySTL;

template<typename T>
void printQueue(my_queue<T>& s)
{
    for(int i=0;i<s.size();i++)
    {
        cout<<s[i]<<" ";
    }
    cout<<endl;
}

void test_queue()
{
    my_queue<int> q1;
    q1.push(11);
    q1.push(2);
    q1.push(31);
    q1.push(56);
    q1.push(876);
    cout << q1.size() << endl;
    printQueue(q1);
    cout << "front:" << q1.front() << endl;
    cout << "back:" << q1.back() << endl;
    q1.pop();
    printQueue(q1);
    cout << q1.size() << endl;
}

int main(int argc, char *argv[])
{
    test_queue();

    return 0;
}