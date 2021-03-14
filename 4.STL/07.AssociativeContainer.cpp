/*

关联容器与顺序容器一样，是一种特定类型对象的集合，不同的是，元素是通过 关键字 而不是位置来索引。
关联容器支持高效的关键字查找和访问。

map：map中的元素是 关键字-值(key-value)对，关键字起到索引的作用，值表示与索引相关联的数据
set：set中每个元素只包含一个关键字，set支持高效的关键字查询操作，即检查一个关键字是否在set中

*/

#include <iostream>
#include <map>
#include <set>
using namespace std;

/*

关联容器的额外的类型别名

key_type      此容器类型的关键字类型
mapped_type   每个关键字关联的类型，只适用于map
value_type    对于set，与key_type相同
              对于map，为pair<const key_type,mapped_type>

*/

void test()
{
    set<string>::value_type v1; // v1 是一个string
    set<string>::key_type v2;   // v2 是一个string

    map<string, int>::value_type v3;  // v3 是一个pair<const string, int>
    map<string, int>::key_type v4;    // v4 是一个string
    map<string, int>::mapped_type v5; // v5 是一个int
}

/*

Test1: map使用

*/
void test1_map()
{
    // map的构造方法
    map<char, int> tmpMap1{{'A', 10}, {'B', 11}, {'C', 12}};
    map<char, int> tmpMap2 = {{'D', 13}, {'E', 14}};
    map<char, int> tmpMap3(tmpMap2);
    map<char, int> tmpMap4 = tmpMap1;

    pair<char, int> p1('F', 15);
    pair<char, int> p2('G', 16);
    pair<char, int> p3('H', 17);
    pair<char, int> p4('I', 18);
    map<char, int> tmpMap5 = {p1, p2, p3, p4, p4, p4};     // 重复元素
    cout << "tmpMap5.size():\t" << tmpMap5.size() << endl; // 4
    cout << "tmpMap5.max_size():\t" << tmpMap5.max_size() << endl;

    map<string, int> tmpMap6 = {make_pair("Good", 1), make_pair("Better", 2), make_pair("Best", 3)};

    // 遍历
    map<string, int>::iterator ite;
    for (ite = tmpMap6.begin(); ite != tmpMap6.end(); ite++)
    {
        cout << (*ite).first << "," << ite->second << endl;
    }

    map<char, int>::const_iterator cite;
    for (cite = tmpMap5.begin(); cite != tmpMap5.end(); cite++)
    {
        cout << cite->first << "," << cite->second << endl;
    }

    // 反向遍历
    map<char, int>::reverse_iterator rite;
    for (rite = tmpMap5.rbegin(); rite != tmpMap5.rend(); rite++)
    {
        cout << rite->first << "," << rite->second << endl;
    }
}

/*

Test2: 添加 和 访问 元素

*/
void test2_map()
{
    map<char, int> tmpMap1{{'A', 10}, {'B', 11}, {'C', 12}};

    // map添加
    // map<char, int> tmpMap1{{'A', 10}, {'B', 11}, {'C', 12}};
    tmpMap1['D'] = 15;
    tmpMap1['E'] = 16;
    tmpMap1.insert(make_pair('G', 20));
    tmpMap1.insert({'K', 34});
    map<char, int>::iterator ite_char;
    for (ite_char = tmpMap1.begin(); ite_char != tmpMap1.end(); ite_char++)
    {
        cout << (*ite_char).first << "," << ite_char->second << endl;
    }

    // map的元素访问
    // map<char, int> tmpMap1{{'A', 10}, {'B', 11}, {'C', 12}};
    cout << tmpMap1['A'] << endl;       // 10
    cout << tmpMap1.at('B') << endl;    // 11
    cout << tmpMap1.count('A') << endl; // 1
    cout << tmpMap1.count('B') << endl; // 1
    cout << tmpMap1.count('M') << endl; // 0

    // map查找
    map<char, int>::iterator i = tmpMap1.find('K');
    if (i != tmpMap1.end())
    {
        cout << "Found K" << endl;
        cout << i->first << "," << i->second << endl;
    }
    else
    {
        cout << "Not found K" << endl;
    }
}

/*

Test3: 从关联容器中删除元素


c.erase(k)     从c中删除每个关键字为k的元素，返回一个size_type值，指出删除的元素的数量

c.erase(p)     从c中删除迭代器p指定的元素，p必须指向c中一个真实元素，不能等于c.end()，
               返回一个指向p之后元素的迭代器，若p指向c中的尾元素，则返回c.end()

c.erase(b,e)   删除迭代器对b和e所表示范围中的元素，返回e

*/
void printMap(map<string, int>&tmpMap)
{
    for(map<string, int>::iterator ite = tmpMap.begin();ite != tmpMap.end();ite++)
    {
        cout<<ite->first<<","<<ite->second<<endl;
    }
    cout<<"========================="<<endl;
}
void test_delete_map()
{
    map<string, int> map1 = {{"Good", 1}};
    map1.insert({"Hello", 12});
    map1.insert(make_pair("Chengdu", 13));
    map1["Key"] = 4;
    map1["Fire"] = 9;
    map1["Bob"] = 19;
    printMap(map1);

    // 删除关键字为"Fire"的元素
    size_t i = map1.erase("Fire");
    size_t j = map1.erase("first");
    cout << "i =  " << i << endl; // 1
    cout << "j =  " << j << endl; // 0
    printMap(map1);

    // 查找Good，删除，并返回下一个元素的迭代器
    auto t = map1.find("Good");
    map<string, int>::iterator ite = map1.erase(t);
    cout<<ite->first<<","<<ite->second<<endl;
    printMap(map1);
    
    // 全部删除
    map1.erase(map1.begin(), map1.end());
    printMap(map1);
}

/*

Test4: 测试set的使用

*/
void printSet(set<string>&s)
{
    for(set<string>::iterator ite = s.begin();ite != s.end();ite++)
    {
        cout<<*ite<<" "<<endl;
    }
    cout<<"==================="<<endl;
}

void test4_set()
{
    set<int>s1 = {1,2,3,4,5,6,7,7,7,7,7};
    cout<<"s1.size() = "<<s1.size()<<endl;  // 7

    set<string>tmpS1 = {"I", "you", "He"};
    set<string>tmpS2{"Him", "Me", "Her", "Them"};
    set<string>tmpS3(tmpS1);
    set<string>tmpS4 = tmpS2;
    
    // 添加
    tmpS2.insert("Us");
    printSet(tmpS2);
    tmpS2.insert(tmpS1.begin(), tmpS1.end());
    printSet(tmpS2);

    tmpS2.insert({"They", "Our"});
    printSet(tmpS2);

    // 访问

    // cout<<tmpS2["Us"]<<endl;  set没有[]访问操作

    set<string>::iterator i = tmpS2.find("Us");
    if(i != tmpS2.end())
    {
        cout<<"Found Us"<<endl;
    }
    else
    {
        cout<<"Not found Us"<<endl;
    }

    size_t j = tmpS2.count("You");
    cout<<"tmpS2.count(\"You\") = "<<j<<endl;  // 0
}

/*

Test5: multiset  multimap

*/
void printMultiSet(multiset<int>&ms)
{
    for(multiset<int>::iterator ite = ms.begin();ite != ms.end();ite++)
    {
        cout<<*ite<<" ";
    }
    cout<<endl;
}
void test_multi_()
{
    multiset<int>ms1 = {11,2,3,1,1,5,6,7,8,9,4,0,9};
    printMultiSet(ms1);
    multiset<int>ms2{11,12,13,13,14};

    // 插入
    ms1.insert(ms2.begin(), ms2.end());
    printMultiSet(ms1);
    ms1.insert(2);
    printMultiSet(ms1);

    // multiset 不支持[]访问
    // cout<<ms1[3];  // Wrong

    cout<<"m1.count(1) = "<<ms1.count(1)<<endl;
    cout<<"m1.count(2) = "<<ms1.count(2)<<endl;
    cout<<"m1.count(12) = "<<ms1.count(12)<<endl;
    cout<<"m1.count(20) = "<<ms1.count(20)<<endl;


    // 删除
    // 删除multiset中所有1
    ms1.erase(1);
    printMultiSet(ms1);
}

void test_word_count()
{
    string input;
    set<string> exclude_word{"the", "The", "is", "a", "to", "or"};

    map<string, int> word_count;
    while (cin >> input)
    {
        if (exclude_word.find(input) == exclude_word.end())
        {
            word_count[input]++;
        }
    }
    for (auto i = word_count.begin(); i != word_count.end(); i++)
    {
        cout << (*i).first << "  occur\t" << (*i).second << " times" << endl;
    }
}

int main()
{
    // test1_map();

    // test2_map();

    // test3_delete_map();

    // test4_set();

    test_multi_();

    // test_word_count();
}