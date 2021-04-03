#include <iostream>
using namespace std;

#include <memory>
#include <intrin.h>
#include <vector>
#include <array>

class A
{
    public:
    A(int ia = 0):a(ia)
    {
        print();
    }
    void print();
    private:
    int a;
};

void A::print()
{
    cout << "A::a = " << a << endl;
}

class A2
{
    public:
    A2(int ia = 0):a(ia)
    {
        print();
    }
    inline void print()
    {
        cout << "A2::a = " << a << endl;
    }
    private:
    int a;
    static int b;
};

int main()
{
    A a1(5);
    a1.print();

    cout << sizeof(A2) << endl;

    return 0;
}