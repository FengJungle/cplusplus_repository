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
    my_deque<int> d1(3, 0);
	d1.push_back(9);
	d1.push_back(98);
	d1.push_front(198);
	print(d1);
	cout << d1.size() << endl;

	d1.pop_back();
	print(d1);
}

int main(int argc, char* argv[])
{
    test_deque();



    return 0;
}