#include <iostream>
#include <string>
#include <math.h>
using namespace std;


/*    友元    */

/* 
1. 类的友元函数
(1). 访问类的私有成员，打破封装
(2). 重载运算符
*/

namespace FriendFunction
{
    class Line
    {
    public:
        Line(int ix1 = 0, int iy1 = 0, int ix2 = 0, int iy2 = 0) : x1(ix1), y1(iy1), x2(ix2), y2(iy2) {}

        // 友元函数：打印线段起止点坐标
        friend void show(Line &line);

        // 转换函数
        operator int()
        {
            int distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            return distance;
        }

    private:
        // 起止点坐标
        int x1, y1, x2, y2;

        // 友元函数重载+
        friend Line operator+(Line &line1, Line &line2);
    };

    void show(Line &line)
    {
        cout << "(" << line.x1 << ", " << line.y1 << ") -> ( " << line.x2 << ", " << line.y2 << ")" << endl;
    }

    Line operator+(Line &line1, Line &line2)
    {
        Line ret;
        ret.x1 = line1.x1;
        ret.y1 = line1.y1;
        ret.x2 = line2.x2;
        ret.y2 = line2.y2;
        return ret;
    }

    void test()
    {
        Line l1(0, 0, 10, 10);
        show(l1);
        int distance = l1;
        cout << "distance = " << distance << endl;

        Line l2(15, 20, 30, 40);
        show(l2);

        Line l3 = l1 + l2;
        show(l3);
    }
} // namespace FriendFunction

/*
2. 类之间的友元关系

(1). 如果一个类指定了友元类，则友元类的成员函数可以访问此类的所有成员。
(2). 友元关系不存在传递性，每个类负责控制自己的友元类或友元函数。

*/

namespace FriendClass
{
    // 前向声明
    class A;

    class B
    {
    public:
        B(int ix = 0, string istr = "") : x(ix), str(istr)
        {
        }

    private:
        // 声明A为B的友元类，A可以访问B的私有成员
        // 友元类的声明不受权限控制，因为友元类A不是B的成员
        friend class A;
        int x;
        string str;
    };

    class A
    {
    public:
        A()
        {
        }
        void show(B &b)
        {
            // A是B的友元类，所以A可以访问B的私有成员
            cout << "(" << b.x << ", " << b.str << ")" << endl;
        }
    };

    void test()
    {
        B b(10, "B class");
        A a;
        a.show(b);
    }
} // namespace FriendClass

int main()
{
    FriendFunction::test();
    // FriendClass::test();
}