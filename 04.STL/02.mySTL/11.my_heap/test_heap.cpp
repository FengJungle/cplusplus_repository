#include "my_heap.h"

#include <iostream>
using namespace mySTL;
using namespace std;

void test()
{
    my_max_heap<int> h1;
    cout << h1.size() << endl;
    h1.push_heap(15);
    h1.push_heap(13);
    h1.push_heap(44);
    h1.push_heap(24);
    h1.push_heap(14);
    h1.push_heap(79);
    h1.push_heap(100);
    cout << h1.size() << endl;
    cout << h1.getMax() << endl;
    h1.pop_heap();
    cout << h1.getMax() << endl;
    h1.pop_heap();
    cout << h1.size() << endl;
    h1.push_heap(199);
    cout << h1.size() << endl;
    cout << h1.getMax() << endl;
    h1.push_heap(1199);
    cout << h1.getMax() << endl;
    h1.push_heap(1299);
    cout << h1.getMax() << endl;
    h1.push_heap(1399);
    cout << h1.getMax() << endl;

    cout<<"=============="<<endl;
    int arr[5] = {10,92,9,0,12};
    my_max_heap<int>h2(arr, 5);
    cout<<h2.getMax()<<endl;h2.pop_heap();
    cout<<h2.getMax()<<endl;h2.pop_heap();
    cout<<h2.getMax()<<endl;h2.pop_heap();
    cout<<h2.getMax()<<endl;h2.pop_heap();
}

int main(int argc, char *argv[])
{
    test();

    return 0;
}