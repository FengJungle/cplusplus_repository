#include <iostream>
#include <string>
using namespace std;

/*

Test1: 构造string

*/
void test1()
{
    // 从一个const char* 构造string
    const char *ch1 = "Chengdu I love you!";
    string str1 = string(ch1, 2); // "Ch"
    string str2 = string(ch1);    // "Chengdu I love you!"
    cout << str1 << endl;

    char ch2[] = "Beijing is a big city";
    string str3(ch2);       // "Beijing is a big city"
    string str4(ch2, 0, 4); // "Beji"
    string str5(ch2, 7);    // "Beijing"
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;

    // 从一个string构造string
    string str6 = "China is a country!";
    string str7("Beijing is the capital.");
    string str8 = str7;
    string str9(str6);
    cout << str6 << endl;
    cout << str7 << endl;
    cout << str8 << endl;
    cout << str9 << endl;

    string str10(str6, 6);    // "is a country!"
    string str11(str6, 0, 5); // "China"
    cout << str10 << endl;
    cout << str11 << endl;
}

/*

Test2: 测试substr

*/
void test2()
{
    string str1 = "As a student in school, you'd better behave yourself";
    cout << str1 << endl;

    // 从第0个位置开始，拷贝12个字符
    string str2 = str1.substr(0, 12); // "As s student"
    cout << str2 << endl;

    // 从第5个位置开始，拷贝7个字符
    string str3 = str1.substr(5, 7); // "student"
    cout << str3 << endl;

    // 从第24个位置开始，拷贝至最后
    string str4 = str1.substr(24); // "you'd better behave yourself"
    cout << str4 << endl;
}

/*

Test3: 测试插入 insert 和 append

*/
void test3()
{
    string str1 = "Sichuan Province";
    cout << str1 << endl;

    // 指定位置插入2个'!'
    str1.insert(str1.size(), 2, '!'); // Sichuan Province!!
    cout << str1 << endl;

    str1.insert(8, "is a ");
    cout << str1 << endl; // "Sichuan is a Province!!"

    str1.append("Yes, it is"); // "Sichuan is a Province!!Yes, it is"
    cout << str1 << endl;
}

/*

Test4: 测试replace

*/
void test4()
{
    string str1 = "Good better worst";
    cout << str1 << endl;
    // 从str1的第12个位置擦除5个字符，并用指定字符串替代
    str1.replace(12, 5, "best");
    cout << str1 << endl; // "Good better best"
}

/*

Test5: 测试find

*/
void test5()
{
    string str1 = "Bad worse worst";
    size_t pos = str1.find("a"); // pos = 1
    cout << pos << endl;

    size_t pos2 = str1.find("st"); // pos2 = 13;
    cout << pos2 << endl;

    auto pos3 = str1.find("c"); // pos3 =
    cout << pos3 << endl;

    auto pos4 = str1.find_first_of('w'); // 4
    cout << "find_first_of('w'):" << pos4 << endl;

    auto pos5 = str1.find_first_not_of('w'); // 0
    cout << "find_first_not_of('w'):" << pos5 << endl;

    auto pos6 = str1.find_last_of('o'); // 11
    cout << "find_last_of('o'):" << pos6 << endl;

    auto pos7 = str1.find_last_not_of('o'); // 14
    cout << "find_last_not_of('o'):" << pos7 << endl;
}

/*

Test6: 数值转换

*/
void test6()
{
    int a = 10;
    double b = 1.99;
    float c = 19.23f;
    string str1 = to_string(a);
    string str2 = to_string(b);
    string str3 = to_string(c);
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;

    string str4 = "123.456";

    // 转换为整数
    int num1 = stoi(str4);                  // 123
    long num2 = stol(str4);                 // 123
    unsigned long num3 = stoul(str4);       // 123
    long long num4 = stoll(str4);           // 123
    unsigned long long num5 = stoull(str4); // 123
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;
    cout << "num4 = " << num4 << endl;
    cout << "num5 = " << num5 << endl;

    // 转换为小数
    double num6 = stod(str4);
    float num7 = stof(str4);
    long double num8 = stold(str4);
    cout << "num6 = " << num6 << endl; // 123.456
    cout << "num7 = " << num7 << endl; // 123.456
    cout << "num8 = " << num8 << endl; // 123.456

    string str5 = "abd1234";
    auto num9 = stoi(str5.substr(str5.find_first_of("1"))); // 1234
    cout << "num9 = " << num9 << endl;
}

int main()
{
    // test1();

    // test2();

    // test3();

    // test4();

    // test5();

    test6();

    return 0;
}