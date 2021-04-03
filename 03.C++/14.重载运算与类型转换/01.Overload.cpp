/*
1. 重载：由关键字operator和其后要定义的运算符号共同组成。重载的运算符也包含返回类型、参数列表和函数体。
(1). 如果一个运算符函数是成员函数，则它的左侧第一个运算对象绑定到隐式的this指针；
(2). 不能被重载的运算符： ::    .*    .    ?:
(3). 不应该重载的运算符：
    a. 逻辑与、逻辑或、逗号运算符：指定了运算对象的求值顺序，这些规则无法应用到重载的运算符上。
    b. 取地址：作用于类对象是有内置含义。
(4). 选择作为成员函数还是非成员函数：
    a. 赋值(=)、下标([])、调用(())、成员访问箭头(->)运算符必须是成员函数。
    b. 具有对称性的运算符通常应该是非成员。

*/

/*

Example: 设计一个Point类
成员：坐标x，坐标y
方法：打印Point信息
重载：+、-、==、!=、<、>、<<
转换函数：int
*/

#include <iostream>
using namespace std;
#include <math.h>

namespace Feng_Point
{
    class Point
    {
    public:
        // 默认构造函数：初始化列表
        Point(int ix = 0, int iy = 0) : x(ix), y(iy)
        {
        }
        // 析构函数：没有指针，可以不必设计
        ~Point()
        {
        }

        // 打印函数：打印Point信息
        void show()
        {
            cout << "(" << this->x << "," << this->y << ")" << endl;
        }

        // 转换函数：Point -> int
        operator int()
        {
            int distance = sqrt(x * x + y * y);
        }

        // 成员函数重载
        // ==
        bool operator==(Point &p)
        {
            int dis1 = *this;
            int dis2 = p;
            return dis1 == dis2;
        }
        // !=
        bool operator!=(Point &p)
        {
            return !(*this == p);
        }
        // <
        bool operator<(const Point &p)
        {
            return x < p.x && y < p.y;
        }
        // >
        bool operator>(Point &p)
        {
            return (p < (*this)) && ((*this) != p);
        }
        // ++前置
        Point operator++()
        {
            this->x++;
            this->y++;
            return *this;
        }
        // ++后置
        Point operator++(int)
        {
            Point old = *this;
            this->x++;
            this->y++;
            return old;
        }

        // 友元函数重载
        friend Point operator+(const Point &p1, const Point &p2);
        friend Point operator-(const Point &p1, const Point &p2);
        friend ostream &operator<<(ostream &os, const Point &p);

    private:
        int x;
        int y;
    };

    Point operator+(const Point &p1, const Point &p2)
    {
        Point result;
        result.x = p1.x + p2.x;
        result.y = p1.y + p2.y;
        return result;
    }

    Point operator-(const Point &p1, const Point &p2)
    {
        Point result;
        result.x = p1.x - p2.x;
        result.y = p1.y - p2.y;
        return result;
    }

    ostream &operator<<(ostream &os, const Point &p)
    {
        os << "(" << p.x << "," << p.y << ")" << endl;
        return os;
    }
} // namespace Feng_Point

int main()
{
    using namespace Feng_Point;

    // 1. 测试: show函数和转换函数
    cout << "\n1. Test: show and ConversionFunction==================================" << endl;
    Point p1(1,2);
    Point p2(3,4);
    p1.show();
    p2.show();
    int dis_p2 = p2;
    cout<<"dis_p2 = "<<dis_p2<<endl;

    // 2. 测试：重载+、-、<<
    cout << "\n2. Test: +, -, <<==================================" << endl;
    Point p3 = p1 + p2;
    Point p4 = p1 - p2;
    cout << "p1:" << p1
         << "p2:" << p2
         << "p3:" << p3
         << "p4:" << p4;

    // 3. 测试：重载==、!=
    cout << "\n3. Test: ==, != ==================================" << endl;
    Point p6(10, 20), p7(20, 10), p8(10, 10);
    if(p6 == p7){
        cout << "p6 == p7" << endl;
    }
    else{
        cout << "p6 != p7" << endl;
    }
    if(p8 == p7){
        cout << "p8 == p7" << endl;
    }
    else{
        cout << "p8 != p7" << endl;
    }

    // 4. 测试：重载+++
    cout << "\n4. Test: ++ ==================================" << endl;
    Point p9(11,22);
    p9.show();
    
    cout<<"p9++: ";
    Point p10 = p9++;
    p10.show();

    cout<<"++p9: ";
    Point p11 = ++p9;
    p11.show();

    return 0;
}