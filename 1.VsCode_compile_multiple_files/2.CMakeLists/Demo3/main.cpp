#include <iostream>
using namespace std;

#include "common/common.h"
#include "funclib/funclib.h"

int main()
{
    cout << "Hello world!" << endl;
    printBasicInfo();

    int a = 0;
    int b = 0;
    cout << "input a = ";
    cin >> a;
    cout << "input b = ";
    cin >> b;
    cout << "a + b = " << add(a, b) << endl;
    cout << "a - b = " << sub(a, b) << endl;

    return 0;
}
