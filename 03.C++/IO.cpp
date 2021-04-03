// 可见域的操作
#include <iostream>
// 文件的操作
#include <fstream>
// 字符串的操作
#include <sstream>

#include <string>
#include <vector>
using namespace std;



/*
-----------------------------------------------------------
 头文件                类型                                
 ----------------------------------------------------------
iostream     istream, wistream 从流读取数据                
             ostream, wostream 向流写入数据
             iostream, wiostream 读写流
-----------------------------------------------------------
             ifstream, wifstream 从文件读入数据
fstream      ofstream, wofstream 向文件写入数据
             fstream,  wfstream  读写文件
-----------------------------------------------------------
             istringstream, wistringstream 从string读取数据
sstream      ostringstream, wostringstream 向string写入数据
             stringstream,  wstringstream  读写string
-----------------------------------------------------------

*/

/* 
3. string流

istringstream, wistringstream 从string读取数据
ostringstream, wostringstream 向string写入数据

*/
namespace IO_String
{

    struct PersonInfo
    {
        string name;
        string phones;
    };

    void test()
    {
        // 保存输入的一行和单词
        string line, word;
        // 保存来自输入的所有记录
        PersonInfo people[5];

        for (int i = 0; i < 5; i++)
        {
            // getline从标准输入读取整条输入
            if (getline(cin, line))
            {
                // 显示构造函数：
                // 用string对象line的拷贝用于初始化istringstream对象record
                istringstream record(line);

                // 从string中读取数据
                // 读取名字
                record >> people[i].name;
                // 读取号码
                record >> people[i].phones;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            cout << people[i].name << "\t" << people[i].phones << endl;
        }
    }
} // namespace IO_String

int main()
{
    IO_String::test();


    return 0;
}