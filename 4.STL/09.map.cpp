#include <iostream>
using namespace std;

#include <map>

void test_map()
{
	map<char, int> m1{{'a', 2}, {'d', 10}};

	// 1. 插入
	pair<char, int> p1{'d', 9};
	m1.insert(p1); // 重复插入'd'会失败
	m1.insert(make_pair<char, int>('r', 13));
	m1.insert({'b', 7});
	m1['p'] = 19;
	// 2. 遍历
	for(map<char, int>::iterator it = m1.begin();it != m1.end();it++)
	{
		cout << it->first << "\t" << it->second << endl; // 已根据key排序：(a,2),(b,7),(d,10),(p,19),(r,13)
	}
	// 3. 访问
	cout << m1['a'] << endl; // 2
	cout << m1['d'] << endl; // 10
	cout << m1['f'] << endl; // 0

	// 4. 查找
	map<char, int>::iterator p = m1.find('d');
	if (p != m1.end())
		cout << p->second << endl; // 10
	
	// 5. 删除
	m1.erase(p); // 删除迭代器指定位置元素
	m1.erase('a'); // 删除指定键值
	m1.erase(m1.find('b'), m1.find('p')); // 删除迭代器指定范围
}

int main(int argc, char* argv[])
{
    test_map();
    return 0;
}