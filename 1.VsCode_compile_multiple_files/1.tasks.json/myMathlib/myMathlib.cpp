#include "myMathlib.h"

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int sum(int arr[], int number)
{
    int sum = 0;
    for (int i = 0; i < number; i++)
    {
        sum += arr[i];
    }
    return sum;
}