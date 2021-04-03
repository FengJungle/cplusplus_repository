#include <iostream>
using namespace std;

/*

1. 类模板

(1). 如果一个成员函数没有被使用，则它不会被实例化。成员函数只有在被用到时才进行实例化。
(2). 类模板的static成员：
     每个实例化的类都有自己的static成员实例，相同类型的对象共享同一个static对象，不同类型的对象的static对象是不一样的
*/

namespace ClassTemplte1
{
    /***********************************************************/
    // 定义模板类Array
    template <typename T>
    class Array
    {
    public:
        Array(int isize = 1);
        Array(initializer_list<T> il);
        ~Array();
        void print();
        T &operator[](int index);

        // static成员
        static int count;

    private:
        T *arr;
        int size;
    };

    template <typename T>
    int Array<T>::count = 0;

    template <typename T>
    Array<T>::Array(int isize)
    {
        this->size = isize;
        this->arr = new T[size]();
        count += isize;
    }

    template <typename T>
    Array<T>::Array(initializer_list<T> il)
    {
        this->size = il.size();
        this->arr = new T[size]();
        for (int i = 0; i < size; i++)
        {
            arr[i] = *(il.begin() + i);
        }
        count += size;
    }

    template <typename T>
    Array<T>::~Array()
    {
        cout << "Delete" << endl;
        delete[] arr;
        arr = nullptr;
    }

    template <typename T>
    void Array<T>::print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << ":\t" << arr[i] << endl;
        }
    }

    template <typename T>
    T &Array<T>::operator[](int index)
    {
        return arr[index];
    }

    /***********************************************************/
    // 自定义一个类Person
    class Person
    {
    public:
        Person(string iname = "John", int iage = 16) : name(iname), age(iage) {}
        friend ostream &operator<<(ostream &os, const Person &person);

    private:
        string name;
        int age;
    };
    ostream &operator<<(ostream &os, const Person &person)
    {
        os << "Name:\t" << person.name << "\tAge:\t" << person.age;
        return os;
    }
    /*************************************************************/

    void test1()
    {
        {
            Array<int> IntArray(5);
            IntArray[2] = 10;
            IntArray[4] = 14;
            IntArray.print();
            cout << "Array<int> count = " << Array<int>::count << endl;

            Array<int> IntArray2(2);
            cout << "Array<int> count = " << Array<int>::count << endl;
        }

        Array<char> CharArray = {'A', 'B', 'C', 'D'};
        CharArray.print();
        cout << "Array<char> count = " << Array<char>::count << endl;

        Array<Person> PersonArray(3);
        PersonArray[0] = string("Jungle");
        PersonArray[1] = string("Bob");
        PersonArray[2] = string("Alice");
        PersonArray.print();
        cout << "Array<Person> count = " << Array<Person>::count << endl;
    }
} // namespace ClassTemplte1

/*
 2. 成员模板

 (1). 一个类（普通类或类模板）可以包含本身是模板的成员函数，即成员模板。
 (2). 成员模板不能是虚函数。

*/

namespace MemberTemplate
{
    class DebugPrint
    {
    public:
        DebugPrint() {}

        // 成员模板
        template <typename T>
        void print(T *t);

    private:
    };

    template <typename T>
    void DebugPrint::print(T *t)
    {
        cout << *t << endl;
    }

    void test2()
    {
        DebugPrint * debug = new DebugPrint();

        int a = 10;
        char b = 'A';
        string str = "Chengdu";
        debug->print(&a);
        debug->print(&b);
        debug->print(&str);
    }
} // namespace MemberTemplate

int main()
{
    // ClassTemplte1::test1();
    MemberTemplate::test2();
}