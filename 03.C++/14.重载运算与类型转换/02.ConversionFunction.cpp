/*

1. 类型转换运算符
    operator type() const;
类型转换运算符没有显示的返回类型，没有形参，必须定义为类的成员函数，一般被定义为const成员，因为通常不应该改变待转换对象的内容。

2. 显示的类型转换运算符
防止类型自动转换产生的异常效果，可以使用显示的类型转换
    explicit operator type() const;
*/


#include <iostream>
#include <math.h>
using namespace std;

class Point
{
public:

    // 默认构造函数
    Point(double ix = 0.00, double iy = 0.00):x(ix), y(iy)
    {

    }

    // 析构函数
    ~Point()
    {

    }

    // 打印Point信息
    void show()
    {
        cout << "x = " << this->x << ", y = " << this->y << endl;
    }

    // 转换函数：Point转换成double
    // 1. 无返回值
    // 2. 以operator开头
    // 3. 目的类型可以是内置类型，也可以是自定义类型： 目的类型()
    // 4. const：不改变原有对象内容
    operator double() const
    {
        // 转换的过程有开发者自己定义实现
        double distance = 0.00;
        distance = sqrt(this->x * this->x + this->y * this->y);

        // 返回值类型为double，代表Point转为double
        return distance;
    }

    // 显示的类型转换
    explicit operator int() const
    {
        int ret = 0;
        ret = x * x + y * y;
        return ret;
    }

private:
    double x;
    double y;
};


int main()
{
    Point p1(3.0, 4.0);
    p1.show();

    // 目的类型为double, 源类型为Point
    // 此处会调用转换函数，将Point转换成double
    double length = p1;
    cout << "length = " << length << endl;

    // 隐式类型转换
    Point p2 = 9.00;
    p2.show();

    // 显示类型转换
    Point p3(5, 6);
    int ret1 = static_cast<int>(p3);
    cout << ret1 << endl;

    return 0;
}