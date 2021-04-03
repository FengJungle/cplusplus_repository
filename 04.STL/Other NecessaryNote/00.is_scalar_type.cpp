#include <iostream>
using namespace std;

#include <type_traits>

/*

https://en.cppreference.com/w/cpp/types/is_scalar

标量类型（Scalar type）是相对复合类型（Compound type）来说的：标量类型只能有一个值，而复合类型可以包含多个值。复合类型是由标量类型构成的。

is_scalar的实现：
template<class _Ty>
	struct is_scalar
		: bool_constant<is_arithmetic_v<_Ty>
		|| is_enum_v<_Ty>
		|| is_pointer_v<_Ty>
		|| is_member_pointer_v<_Ty>
		|| is_null_pointer_v<_Ty>>
	{	// determine whether _Ty is a scalar type
	};

*/

void test_scalar()
{
    // 基本数据类型都是标量
    cout << "is_scalar<char>:" << is_scalar<char>::value << endl;                     // 1
    cout << "is_scalar<char*>:" << is_scalar<char *>::value << endl;                  // 1
    cout << "is_scalar<unsigned char>:" << is_scalar<unsigned char>::value << endl;   // 1
    cout << "is_scalar<signed char>:" << is_scalar<signed char>::value << endl;       // 1
    cout << "is_scalar<short>:" << is_scalar<short>::value << endl;                   // 1
    cout << "is_scalar<unsigned short>:" << is_scalar<unsigned short>::value << endl; // 1
    cout << "is_scalar<int>:" << is_scalar<int>::value << endl;                       // 1
    cout << "is_scalar<unsigned int>:" << is_scalar<unsigned int>::value << endl;     // 1
    cout << "is_scalar<bool>:" << is_scalar<bool>::value << endl;                     // 1
    cout << "is_scalar<long>:" << is_scalar<long>::value << endl;                     // 1
    cout << "is_scalar<unsigned long>:" << is_scalar<unsigned long>::value << endl;   // 1
    cout << "is_scalar<float>:" << is_scalar<float>::value << endl;                   // 1
    cout << "is_scalar<double>:" << is_scalar<double>::value << endl;                 // 1
    cout << "is_scalar<double*>:" << is_scalar<double *>::value << endl;              // 1

    // void表示标量
    cout << "is_scalar<void>:" << is_scalar<void>::value << endl;                     // 0
    // string不是标量
    cout << "is_scalar<string>:" << is_scalar<string>::value << endl;                 // 0

    int arr_t1[3] = {12, 13, 14};
    enum enum_t2
    {
        RED,
        GREEN,
        BLUE
    };
    struct struct_t3
    {
        int a;
        char b;
        float c;
    };
    class class_t4
    {
    public:
        int a;
        char b;
        float c;
    };
    union union_t5
    {
        int a;
        float b;
    };
    // enum只有一个值，是标量
    cout << "is_scalar<enum_t2>:" << is_scalar<enum_t2>::value << endl;     // 1
    // struct,class和union都不是标量
    cout << "is_scalar<struct_t3>:" << is_scalar<struct_t3>::value << endl; // 0
    cout << "is_scalar<class_t4>:" << is_scalar<class_t4>::value << endl;   // 0
    cout << "is_scalar<union_t5>:" << is_scalar<union_t5>::value << endl;   // 0
}

int main(int argc, char *argv[])
{
    test_scalar();

    return 0;
}