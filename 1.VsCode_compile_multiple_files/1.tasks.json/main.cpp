#include <iostream>
using namespace std;

#include "func/func.h"
#include "myMathlib/myMathlib.h"
#include "common.h"

int maxInt(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    printBasicInfo();

    cout << "Max = " << getMaxDouble(1.00, 13.902) << endl;
    cout << "10 + 29 = " << add(10, 29) << endl;
    getchar();

    return 0;
}