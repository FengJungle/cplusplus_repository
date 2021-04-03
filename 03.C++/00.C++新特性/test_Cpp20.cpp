// #include <compare>
#include <iostream>
 
int main() {
    double foo = 0.0;
    double bar = 1.0;
 
    auto res = foo <=> bar;
 
    if (res < 0)
        std::cout << "foo is less than bar";
    else if (res == 0)
        std::cout << "foo and bar are equal";
    else if (res > 0)
        std::cout << "foo is greater than bar";
}