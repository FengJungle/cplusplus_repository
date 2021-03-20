/*

What is POD? 
 -- https://en.cppreference.com/w/cpp/named_req/PODType

POD类型代表能与旧的C语言数据兼容（其底层二进制能够直接与C库交互）的类型。
（C++20反对使用POD，而使用TrivialType来替代）

Requirements
Either:

1. a scalar type：标量类型
2. a class type (class or struct or union) that:
until C++11
    is an aggregate type：聚合类型
    all non-static members are POD;
    has no members of reference type;
    has no user-defined copy constructor;
    has no user-defined destructor;
since C++11
    is a trivial type;
    is a standard layout type;
    all non-static members are POD;

3. an array of such type.

*/

#include <type_traits>
#include <iostream>
using namespace std;

void test_is_pod()
{
    // 基本数据类型是POD
    cout << "is_pod<char>:" << is_pod<char>::value << endl;                     // 1
    cout << "is_pod<char*>:" << is_pod<char *>::value << endl;                  // 1
    cout << "is_pod<unsigned char>:" << is_pod<unsigned char>::value << endl;   // 1
    cout << "is_pod<signed char>:" << is_pod<signed char>::value << endl;       // 1
    cout << "is_pod<short>:" << is_pod<short>::value << endl;                   // 1
    cout << "is_pod<unsigned short>:" << is_pod<unsigned short>::value << endl; // 1
    cout << "is_pod<int>:" << is_pod<int>::value << endl;                       // 1
    cout << "is_pod<unsigned int>:" << is_pod<unsigned int>::value << endl;     // 1
    cout << "is_pod<bool>:" << is_pod<bool>::value << endl;                     // 1
    cout << "is_pod<long>:" << is_pod<long>::value << endl;                     // 1
    cout << "is_pod<unsigned long>:" << is_pod<unsigned long>::value << endl;   // 1
    cout << "is_pod<float>:" << is_pod<float>::value << endl;                   // 1
    cout << "is_pod<double>:" << is_pod<double>::value << endl;                 // 1
    cout << "is_pod<double*>:" << is_pod<double *>::value << endl;              // 1

    // 引用类型不是pod
    cout << "is_pod<double&>:" << is_pod<double &>::value << endl;              // 0
    cout << "is_pod<int&>:" << is_pod<int &>::value << endl;                    // 0

    // void
    cout << "is_pod<void>:" << is_pod<void>::value << endl;                     // 0
    // string不是POD
    cout << "is_pod<string>:" << is_pod<string>::value << endl;                 // 0

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
    cout << "is_pod<arr_t1>:" << is_pod<int[3]>::value << endl;       // 1
    // enum只有一个值，是标量
    cout << "is_pod<enum_t2>:" << is_pod<enum_t2>::value << endl;     // 1

    cout << "is_pod<struct_t3>:" << is_pod<struct_t3>::value << endl; // 1
    cout << "is_pod<class_t4>:" << is_pod<class_t4>::value << endl;   // 1
    cout << "is_pod<union_t5>:" << is_pod<union_t5>::value << endl;   // 1
}

class A1
{
public:
    int a;
    char b;
    float c;
    void func(){}
};
class A2
{
private:
    int a;
    char b;
    float c;
};
class A3
{
private:
    int a;

public:
    char b;
    float c;
};

class A4
{
private:
    static int a;

public:
    char b;
    float c;
    static int d;
};

class A5:public A1
{
public:
    int a5;
};
class A6:public A1
{
public:
    static int a5;
};

class A7
{
    public:
    // constructor
    A7(){}
};
class A8
{
    public:
    // constructor = default
    A8() = default;
};
class A9
{
    public:
    // destructor
    ~A9(){}
};

void test_pod_class()
{
    // 普通成员访问级别相同，是pod
    cout << "is_pod<A1>:" << is_pod<A1>::value << endl;   // 1
    cout << "is_pod<A2>:" << is_pod<A2>::value << endl;   // 1

    // 有private和public成员，普通成员访问级别不同，布局无序，不是pod
    cout << "is_pod<A3>:" << is_pod<A3>::value << endl;   // 0

    // 尽管有private和public成员，但是普通成员访问级别相同，是pod
    cout << "is_pod<A4>:" << is_pod<A4>::value << endl;   // 1

    // 只要有父类，普通成员必须都在父类中，否则就不是pod，A5中自己定义了普通成员，所以A5不是pod
    // A6中定义的是静态成员，其他普通成员都在父类中，所以A6是pod
    cout << "is_pod<A5>:" << is_pod<A5>::value << endl;   // 0
    cout << "is_pod<A6>:" << is_pod<A6>::value << endl;   // 1

    // 用户定义了构造函数，即使什么都不做，也不再是pod
    cout << "is_pod<A7>:" << is_pod<A7>::value << endl;   // 0
    // 用户用default显示声明使用默认构造函数，是pod
    cout << "is_pod<A8>:" << is_pod<A8>::value << endl;   // 1
    // 用户定义了析构函数，不是pod
    cout << "is_pod<A9>:" << is_pod<A9>::value << endl;   // 0
}

/*

测试pod数据类型的应用

*/
class class_T
{
public:
    int a;
    float b;
    char ch[4];
};
struct struct_T
{
public:
    int a;
    float b;
    char ch[4];
};

void test_pod_application()
{
    class_T t1{10, 3.1315, {'A', 'B', 'C', 'D'}};
    cout<<"sizeof(class_T) = "<<sizeof(class_T)<<endl;
   
    struct struct_T t2 = {0};
    memcpy(&t2, &t1, sizeof(t1));
    cout<<t1.a<<endl;
    cout<<t1.b<<endl;
    cout<<t1.ch[0]<<t1.ch[1]<<t1.ch[2]<<t1.ch[3]<<endl;

    // class_T是POD，直接使用memcpy复制到arr
    char arr[12] = {0};
    memcpy(arr, &t1, sizeof(class_T));
    cout<<(int)arr[0]<<endl;
    cout<<(float)arr[4]<<endl;
    cout<<arr[8]<<endl;
    cout<<arr[9]<<endl;
    cout<<arr[10]<<endl;
    cout<<arr[11]<<endl;
}

int main(int argc, char* argv[])
{
    test_is_pod();

    test_pod_class();

    test_pod_application();

    return 0;
}