#include <iostream>
using namespace std;
#include <unordered_set>

void test_unordered_set()
{
	double arr[5] = {0.98, 3.4, 1.00, -9.04, 43.33};
	unordered_set<double> us1(arr, arr + 5);

	cout<<us1.size()<<endl;          // 5 
	cout<<us1.max_size()<<endl;      // 1152921504606846975
	cout<<us1.bucket_count()<<endl;  // 7
	cout<<us1.bucket_size(0)<<endl;  // 1

	cout<<us1.count(0.98)<<endl;     // 1
	cout<<us1.count(0.0)<<endl;      // 0

	// 插入：插入重复键值无效
	us1.insert(7.77);
	us1.insert(7.77);
	cout<<us1.count(7.77)<<endl;      // 0

	for(int i = 0;i<us1.bucket_count();i++)
	{
		cout << "bucket " << i << " has " << us1.bucket_size(i) << " elements" << endl;
	}
	// 查找
	unordered_set<double>::iterator it = us1.find(-9.04);
	cout << *it << endl; // -9.04

	// 遍历
	for(unordered_set<double>::iterator it = us1.begin();it != us1.end();it++)
	{
		cout << *it << "\t"; // 43.33, -9.04, 1, 7.77, 3.4, 0.98
	}
	cout << endl;
}