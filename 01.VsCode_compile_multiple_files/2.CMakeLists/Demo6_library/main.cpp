#include <iostream>
using namespace std;

#include "mathfunc.h"

int main(int argc, char *argv[])
{
    cout << getMax(10, 2) << endl;
    cout << getMin(10, 2) << endl;
    cout << plus_(10, 2) << endl;
    cout << sub(10, 2) << endl;
    cout << mul(10, 2) << endl;
    cout << div_(10, 2) << endl;

    return 0;
}