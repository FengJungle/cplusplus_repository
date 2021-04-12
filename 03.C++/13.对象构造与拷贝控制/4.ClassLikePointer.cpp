#include <iostream>
#include <memory>
using namespace std;

/*

类的行为像指针：共享状态，当拷贝一个这种类的对象时，副本和原对象使用相同的底层数据

1. 需要为其定义拷贝构造函数和拷贝赋值运算符；
2. 何时销毁底层数据？ 
   -- shared_ptr
   -- 自己实现引用计数
*/

class Book
{
public:
    Book(const char *iname, double iprice) : name(new string(iname)), price(iprice)
    {
        cout << "Book::Constructor" << endl;
        show();
    }

    ~Book()
    {
        cout << "Book::~Book()" << endl;
        if(name.unique())
        {
            cout<<"delete name"<<endl;
        }
    }
    Book(const Book &book)
    {
        cout << "Book::Copy Constructor" << endl;
        this->price = book.price;
        this->name = book.name;
        show();
    }

    Book &operator=(const Book &book)
    {
        cout << "Book::Copy Assignment" << endl;
        if (this == &book)
        {
            cout << "Assign to self" << endl;
            return *this;
        }
        this->price = book.price;
        this->name = book.name;
        return *this;
    }

    void show() const
    {
        cout << "Name:\t" << *(this->name.get()) << "\tPrice:\t" << this->price;
        cout << "\tUse_count:\t" << name.use_count() << endl;
    }

private:
    shared_ptr<string> name;
    double price;
};

void testFunc(Book book)
{

}

void test()
{
    Book *book1 = new Book("Three Gun", 19.99);
    Book book2 = *book1;
    // testFunc(book2);
    // book2.show();

    // delete book1;
    // book2 = book2;
    book2.show();

    {
        Book book3("HELLO", 29.80);
        book3 = book2;
        book2.show();
        book3.show();
    }

    delete book1;
}

int main()
{
    test();

    return 0;
}