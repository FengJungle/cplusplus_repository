#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>

void test_set()
{
	int arr[5] ={10,2,3,14,5};
	set<int> s1(arr, arr + 5); //set内部默认已排序 2,3,5,10,14

	// set不允许键值重复，所以count()的结果或是1或是0
	cout << s1.count(1) << endl; // 0
	cout << s1.count(2) << endl; // 1
	cout << s1.count(4) << endl; // 0

	// 查找find，查找到则返回对应元素位置的迭代器，否则返回end()
	if(s1.find(4) != s1.end())
	{
		cout << "find 4" << endl;
	}
	auto t = s1.find(14); // 返回的是迭代器set<int>::iterator类型，底层是指向红黑树节点的指针
	cout<<*t<<endl; // 14

	// 插入
	s1.insert(24); // 2,3,5,10,14,24
	s1.insert(24);
	cout << s1.count(24) << endl; // 仍旧是1

	// 遍历
	for(set<int>::iterator it = s1.begin();it != s1.end();it++)
	{
		cout<<*it<<"\t";
	}

	// 删除
	// 1. 删除指定键值的元素
	s1.erase(14); // 2,3,5,10,24

	// 2. 删除迭代器指定位置的元素
	s1.erase(s1.find(2)); // 3,5,10,24
	// 2. 删除迭代器指定范围的元素
	set<int>::iterator it1 = s1.find(5);
	set<int>::iterator it2 = s1.find(24);
	s1.erase(it1, it2); // 3,10
}

void test_multiset()
{
	int arr[5] = {10,2,4,4,5};
	multiset<int>s2(arr, arr+5);

	// 1. 遍历
	for(multiset<int>::iterator it = s2.begin();it != s2.end();it++)
	{
		cout<<*it<<"\t"; // 2,4,4,5,10，multiset构造完成后内部默认已排序，且允许重复键值存在
	} 
	// 2. count, 统计multiset中指定键值(或实值)出现的个数
	cout<<s2.count(4)<<endl;  // 2
	cout<<s2.count(1)<<endl;  // 0
	cout<<s2.count(2)<<endl;  // 1
	// 3. 查找find
	multiset<int>::iterator it = s2.find(4); // 返回元素位置的迭代器，或者end()
	cout<<s2.count(*it)<<endl;
	cout<<*it<<endl;
	// s2.count(*it)--;// 不可以通过这种方式减少计数
	// 4. 插入insert
	s2.insert(28); // 2,4,4,5,10,28
	// 5. 删除erase
	s2.erase(4); // 重复键值均被删掉 2,5,10,28
	cout<<s2.count(4); // 0
}

int main()
{
	test_multiset();

	return 0;
}