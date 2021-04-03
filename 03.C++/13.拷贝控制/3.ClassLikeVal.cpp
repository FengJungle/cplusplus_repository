#include <iostream>
using namespace std;

/*

类的行为像一个值

有自己的状态，拷贝一个像值的对象时，副本和原对象完全独立，改变副本不应该影响原对象，反之亦然

*/

class Book
{
public:
    Book() = default;
    Book(const char *iname, size_t inamesize, double iprice) : namesize(inamesize), price(iprice)
    {
        cout << "Book::Constructor"<<endl;

        this->name = new char[inamesize];
        memcpy(this->name, iname, inamesize);
    }

    Book(const Book &book)
    {
        cout << "Book::Copy Constructor"<<endl;
        this->price = book.price;
        this->namesize = book.namesize;
        this->name = new char[book.namesize];
        memcpy(this->name, book.name, book.namesize);
    }

    Book &operator=(const Book &book)
    {
        cout << "Book::Copy Assignment"<<endl;
        if (this == &book)
        {
            return *this;
        }
        this->price = book.price;
        this->namesize = book.namesize;
        this->name = new char[book.namesize];
        memcpy(this->name, book.name, book.namesize);
    }

    ~Book()
    {
        cout << "Book::~Book" << endl;
        delete name;
        name = nullptr;
    }

    void setInfo(const char* iname, int inamesize, double iprice)
    {
        if(this->name != nullptr)
        {
            delete name;
            name = new char[inamesize];
            memcpy(this->name, iname, inamesize);
            this->namesize = inamesize;
            this->price = iprice;
        }
    }

    void show()
    {
        cout << "\tName:\t" << name << "\tPrice:\t" << price << endl;
    }

private:
    char* name;
    double price;
    size_t namesize;
};

void test()
{
    Book *book1 = new Book("Big Three Gun", sizeof("Big Three Gun"), 19.99);
    Book book2 = *book1;

    book1->show();
    book2.show();

    book2.setInfo("NoteBook", sizeof("NoteBook"), 29.90);
    book1->show();
    book2.show();
    
    delete book1;
}

int main()
{
    test();

}