
一、类的声明
/*
#ifndef __MYSTRING__    // 防卫式声明
#define __MYSTRING__

class String
{
    // ……
};

String::function()
{
    // ……
}

Global-function()
{
    // ……
}

#endif 
*/

二、拷贝构造函数和拷贝赋值函数

如果用户没有定义拷贝构造函数和拷贝赋值函数，编译器会为类自动生成。-- 浅拷贝
如果类中有指针，必须自己定义拷贝构造函数和拷贝赋值函数。

/* 测试程序 */
int main()
{
    // 无初始值构造函数
    String s1();

    // 有初始值的构造函数
    String s2("Hello");

    // 拷贝构造函数，以s1为蓝本
    String s3(s1);
    // 重载<<
    cout<<s3<<endl;

    // 拷贝构造函数，因为s4是新创建的对象
    String s4 = s3;

    // 拷贝赋值：s2赋值给s3
    s3 = s2;
    cout<<s3<<endl;
}

三、String类的设计
/*
class String{
public:
    // 构造函数
    String(const char* cstr = 0)
    {
        if(cstr){
            m_data = new char[strlen(cstr)+1 /* '\0' */ ];
            strcpy(m_data, cstr);
        }
        else{ // 未指定初始值
            m_data = new char[1];
            *m_data = '\0';
        }
    }

    // 拷贝构造函数，参数为自己类型的引用
    String(const String& str)
    {
        m_data = new char[strlen(str.m_data)+1];
        strcpy(m_data, str.m_data);
    }

    // 拷贝赋值函数
    String& operator=(const String& str)
    {
        // 检测自我赋值
		// 如果不检测自我赋值，在下面第②步会出错：因为在第一步已经将自己的m_data给delete了
        if(this == &str){
            return *this;
        }

        delete []m_data;                        // ①
        m_data = new char[strlen(m_data)+1];    // ②
        strcpy(m_data, str.m_data);             // ③
        return *this;
    }

    // 析构函数
    ~String()
    {
        delete []m_data;
    }

    // 类里面定义，是inline函数
    char* get_c_str() const{
        return m_data;
    }
    
private:
    //  设计一个指针而不是数组存放字符串，因为不知道字符串的具体大小，
    //  运行时根据使用来动态分配
    char* m_data;
}

// 重载<<运算符
// 不可以是一个成员函数，因为cout一定要在左边
ostream& operator<<(ostream& os, const String& str)
{
    os<<str.get_c_str();
    return os;
}

*/