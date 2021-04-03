#include <iostream>
using namespace std;


#include "my_deque.h"
using namespace mySTL;

void print(my_deque<int> d)
{
    cout << "Hello" << endl;
    for (my_deque<int>::iterator ite = d.begin(); ite != d.end(); ++ite)
    {
        cout << *ite << " ";
    }
    cout << endl;
}

void test_deque()
{
    my_deque<int> d1(1,0);
    cout << d1.size() << endl;
    print(d1);

    for (int i = 1; i <= 9; i++)
        d1.push_back(i);
        
    print(d1);
    cout << d1.size() << endl;
    
    d1.pop_back();
    d1.push_back(10);
    print(d1);

    d1.pop_front();
    print(d1);
}

int main(int argc, char* argv[])
{
    test_deque();



    return 0;
}