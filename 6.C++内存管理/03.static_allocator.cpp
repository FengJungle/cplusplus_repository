#include <iostream>
using namespace std;

// template <typename T>
class _allocator
{
public:
    void* allocate(size_t size)
    {
        cout << "allocate" << endl;
        obj* p;
        if(freeStore == nullptr)
        {
            cout << "chunk" << endl;
            size_t chunk = CHUNK * size;
            freeStore = p = (obj *)malloc(chunk);

            for (int i = 0; i < CHUNK - 1; i++)
            {
                p->next = (obj *)((char *)p + size);
                p = p->next;
            }
            p->next = nullptr;
        }
        p = freeStore;
        freeStore = freeStore->next;
        return p;
    }
    void deallocate(void* p, size_t size)
    {
        cout << "deallocate" << endl;
        ((obj*)p)->next = freeStore;
        freeStore = (obj *)p;
    }
private:
    struct obj
    {
        // embedded pointer
        struct obj* next;
    };
    obj* freeStore{nullptr};
    const int CHUNK = 3;
};

// For test
class Simple
{
private:
    long L;
    string str;
    static _allocator myAlloc;

public:
    Simple(long l):L(l)
    {
        cout << "Simple::constructor" << endl;
    }
    ~Simple()
    {
        cout << "Simple::destructor" << endl;
    }
    static void* operator new(size_t size)
    {
        return myAlloc.allocate(size);
    }
    static void operator delete(void* p, size_t size)
    {
        myAlloc.deallocate(p, size);
    }
};

_allocator Simple::myAlloc;

// For test
class Temp
{
private:
    int x;
    string str;
    static _allocator myAlloc;

public:
    Temp(int ix):x(ix)
    {
        cout << "Temp::constructor" << endl;
    }
    ~Temp()
    {
        cout << "Temp::destructor" << endl;
    }
    static void* operator new(size_t size)
    {
        return myAlloc.allocate(size);
    }
    static void operator delete(void* p, size_t size)
    {
        myAlloc.deallocate(p, size);
    }
};

_allocator Temp::myAlloc;

void test_allocator()
{
    Temp* t1 = new Temp(1);
    Temp* t2 = new Temp(2);
    Temp* t3 = new Temp(3);
    Temp* t4 = new Temp(4);
    delete t1;
    delete t2;
    delete t3;
    delete t4;

    Simple * s1 = new Simple(10);
    Simple * s2 = new Simple(11);
    Simple * s3 = new Simple(12);
    Simple * s4 = new Simple(13);
    Simple * s5 = new Simple(14);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
}

// 宏定义简化
#define DECLARE_POOL_ALLOC()                                                           \
public:                                                                                \
    static void *operator new(size_t size) { return myAlloc.allocate(size); }          \
    static void operator delete(void *p, size_t size) { myAlloc.deallocate(p, size); } \
                                                                                       \
protected:                                                                             \
    static _allocator myAlloc;

#define IMPLEMENT_POOL_ALLOC(class_name) \
    _allocator class_name::myAlloc;

class Test
{
    DECLARE_POOL_ALLOC();

public:
    Test()
    {
        cout << "Test::constructor" << endl;
    }
    ~Test()
    {
        cout << "Test::~destructor" << endl;
    }

private:
    int a;
};
IMPLEMENT_POOL_ALLOC(Test);

void test_macro_allocator()
{
    Test* t1 = new Test();
    Test* t2 = new Test();
    Test* t3 = new Test();
    Test* t4 = new Test();

    delete t1;
    delete t2;
    delete t3;
    delete t4;
}

int main(int argc, char *argv[])
{
    // test_allocator();

    test_macro_allocator();

    return 0;
}