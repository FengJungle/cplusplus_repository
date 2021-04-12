#include <iostream>
using namespace std;

class Exception
{
public:
    Exception()
    {
    }
};

void func_err_int()
{
    throw 1;
}

void func_err_double()
{
    throw 1.01;
}

void func_err_char()
{
    throw "Bad";
}

void func_err_other()
{
    throw 'A';
}

void func_err_Exception()
{
    Exception *e = new Exception();
    throw e;
}

int main()
{
    try
    {
        // func_err_int();
        // func_err_double();
        // func_err_char();
        // func_err_other();
        func_err_Exception();
    }
    catch (int i)
    {
        cout << i << endl;
    }
    catch (double d)
    {
        cout << d << endl;
    }
    catch (const char *str)
    {
        cout << str << endl;
    }
    catch (Exception* e)
    {
        cout << "Exception" << endl;
    }
    catch (...)
    {
        cout << "other error" << endl;
    }

    return 0;
}