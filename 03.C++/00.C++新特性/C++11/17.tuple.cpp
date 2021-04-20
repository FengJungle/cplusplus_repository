#include <iostream>
using namespace std;


// 包含tuple头文件
#include <tuple>

/*

tuple是一个“快速而随意”的数据结构，可以将不同的数据类型组合为一个tuple类型

tuple<T1,T2,...,Tn> t                t是一个tuple，成员数量为n，第i个成员的类型为Ti，所有成员都进行值初始化

tuple<T1,T2,...,Tn> t(v1,v2,...,vn)  初始值vi初始化

make_tuple(v1,v2,...,v3)             返回一个tuple，类型为参数对应类型

t1 == t2       两个tuple具有相同数量的成员，并且成员对应相同。如果某对成员不等，则t1 != t2

get<i>(t)      返回tuple t的第i个数据成员的引用

tuple_size<tupleType>::value   表示给定tuple类型中成员的数量

tuple_element<i, tupleType>::type  表示给定tuple类型中指定成员的类型

*/

void test()
{
    // 1. tuple 构造
    // 值初始化
    tuple<int, float, double> t1;
    // 初始值初始化
    tuple<int, float, double> t2(1, 2.00f, 3.450);
    tuple<int, float, double> t3 = {1, 2.00f, 3.450};
    tuple<int, float, double> t4{1, 2.00f, 3.450};
    if (t3 == t4)
    {
        cout << "t3 == t4" << endl;
    }

    //  使用make_tuple生成tuple
    tuple<int, string> t5 = make_tuple(10, "Good");

    // 2. 使用get获取tuple数据成员
    cout << get<0>(t5) << " " << get<1>(t5) << endl;

    // 3. 使用tuple_size获取tuple成员数量
    cout << tuple_size<tuple<int, string>>::value << endl; // 2
    using tupleType1 = tuple<int, int, double, char>;
    cout << tuple_size<tupleType1>::value << endl; // 4

    typedef tuple<int, short, char, bool, void> tupleType2;
    cout << tuple_size<tupleType2>::value << endl; // 5
}

// 重载：输出tuple
ostream& operator<<(ostream& os, tuple<int, float, string> &t)
{
	os << get<0>(t) << " " << get<1>(t) << " " << get<2>(t);
	return os;
}

int main(int argc, char* argv[])
{
    test();

    tuple<int, float, string> t1(1, 1.2f, "Good");
	cout << t1 << endl;

    return 0;
}