#include <iostream>
using namespace std;


#include "my_list.h"
using namespace mySTL;

void print(my_list<int> &ls)
{
    my_list<int>::iterator ite;
    for (ite = ls.begin(); ite != ls.end(); ite++)
    {
        cout << *ite << "\t";
    }
    cout << endl;
}

void test_list()
{
    my_list<int> la(3, 1);
    cout << la.size() << endl;
    la.insert(la.begin(), 1);
    la.insert(la.end(), 10);
    print(la);

    la.insert(la.begin(), 3, 0);
    print(la);


    my_list<int> la2(4, 99);
    print(la2);
    // la2.insert(la2.begin(), la.begin(), la.end());
    // print(la2);

    my_list<int>la3{1,2,3,4};
    print(la3);
    
    la3.splice(la3.begin(), la2);
    print(la3);

    la3.reverse();
    print(la3);
}

int main(int argc, char* argv[])
{
    test_list();



    return 0;
}