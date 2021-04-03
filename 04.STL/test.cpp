#include <iostream>
#include <initializer_list>
#include <vector>
using namespace std;

class Array
{
public:
    // 默认构造函数
    Array(int isize = 0, int defaultVal = 0):size(isize)
    {
        cout<<"Default Constructor"<<endl;
        for(auto i = 0;i<isize;i++)
        {
            arr.push_back(defaultVal);
        }
    }
    Array(initializer_list<int> il)
    {
        cout<<"Initializer list"<<endl;
        this->size = il.size();
        for (auto i = il.begin(); i != il.end(); i++)
        {
            arr.push_back(*i);
        }
    }
    // 拷贝构造函数
    Array(const Array& RArr)
    {
        cout<<"Copy Constructor"<<endl;
        this->size = RArr.size;
        this->arr = RArr.arr;
    }
    // 赋值运算符
    Array& operator=(const Array& RArr)
    {
        cout<<"Operator = "<<endl;
        if(this == &RArr)
        {
            return *this;
        }
        this->size = RArr.size;
        this->arr = RArr.arr;
        return *this;
    }
    // 
    void push_back(int value)
    {
        this->arr.push_back(value);
        this->size++;
    }
    

    void print()
    {
        for (auto i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

private:
    int size;
    vector<int> arr;
};


class A
{
    public:
    A():c(12)
    {
        cout<<"A()"<<endl;
    }
    ~A(){
        cout<<"~A()"<<endl;
    }
    static const int a = 10;
    static int b;
    const int c;
    void print()
    {
        cout << "a = " << a << "\t b = " << b << "\tc =" << c << endl;
    }
};
int A::b = 11;

template<typename T>
class B
{
    public:
    B()
    {

    }
    T operator()(const T& a)
    {
        T ret = a*a;
        return ret;
    }
    operator char() const{
        return 'A';
    }
};

int main(int argc, char* argv[])
{
    Array a1(10,9);
    a1.print();

    Array a2(5,19);

    Array a3{1,2,3,4,5,6,7,8,9,10};
    a3.print();

    Array a4 = a3;
    a3 = a1;
    a3.push_back(10);
    a3.print();

    A().print();
    cout<<"as"<<endl;
    
    B<int> b;
    cout << b(9) << endl;
    cout<<B<double>()(1.1)<<endl;

    char c = b;
    cout<<c<<endl;

    return 0;
}