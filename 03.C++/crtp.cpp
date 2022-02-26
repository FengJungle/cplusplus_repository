#include <iostream>

#ifdef TEST_CRTP_POLY
template <typename T>
class Base
{
public:
    Base() {}
    virtual ~Base() {}

    void func()
    {
        if (auto t = static_cast<T *>(this))
        {
            t->op();
        }
    }
};

class Derived1 : public Base<Derived1>
{
public:
    Derived1() {}
    void op()
    {
        std::cout << "Derived1::op()" << std::endl;
    }
};

class Derived2 : public Base<Derived2>
{
public:
    Derived2() {}
    void op()
    {
        std::cout << "Derived2::op()" << std::endl;
    }
};

// 辅助函数：完成静态分发
template<typename DerivedClass>
void helperFunc(Base<DerivedClass>& d)
{
    d.func();
}
#endif

#ifdef TEST_CRTP_COUNTER
template<typename T>
class Counter
{
public:
    static int count;
    Counter()
    {
        ++Counter<T>::count;
    }
    ~Counter() 
    {
        --Counter<T>::count;
    }
};
template<typename T>
int Counter<T>::count = 0;

class DogCounter : public Counter<DogCounter>
{
public:
    int getCount()
    {
        return this->count;
    }
};

class CatCounter : public Counter<CatCounter>
{
public:
    int getCount()
    {
        return this->count;
    }
};

void testCounter()
{
    DogCounter d1;
    std::cout << "DogCount : " << d1.getCount() << std::endl;
    {
        DogCounter d2;
        std::cout << "DogCount : " << d1.getCount() << std::endl;
    }
    std::cout << "DogCount : " << d1.getCount() << std::endl;

    CatCounter c1, c2, c3, c4, c5[3];
    std::cout << "CatCount : " << c1.getCount() << std::endl;
}

#endif

int main(int argc, char* argv[]) 
{
    
    return 0;
}