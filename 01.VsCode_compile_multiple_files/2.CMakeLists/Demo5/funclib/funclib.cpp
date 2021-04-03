#include "funclib.h"
#include <iostream>

int add(int a, int b)
{
#ifdef DEBUG
    std::cout << "a = " << a << ", b = " << b << ", a + b = " << a + b << std::endl;
#endif
    return a + b;
}

int sub(int a, int b)
{
#ifdef DEBUG
    std::cout << "a = " << a << ", b = " << b << ", a - b = " << a - b << std::endl;
#endif
    return a - b;
}