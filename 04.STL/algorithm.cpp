/*

STL Algorithm Test

*/

#include <iostream>
using namespace std;

#include <numeric>
#include <vector>

/*

Test1: accumulate
Header file:  <numeric>

*/
void test_accumulate()
{
    int arr[5] = {1, 2, 3, 4, 5};

    // 指定初始值
    int init = 0;
    int result = accumulate(arr, arr + sizeof(arr) / sizeof(int), init /* 初始值为0 */);
    cout << "init = 0, result = " << result << endl;

    init = 10;
    result = accumulate(arr, arr + sizeof(arr) / sizeof(int), init /* 初始值为10 */);
    cout << "init = 10, result = " << result << endl;
}

/*

Test2: adjacent_difference
Header file:  <numeric>
Description: 算出输入序列中相邻元素对的差，并将它们保存到另一个序列中.
第一个元素会被原封不动地复制到新的序列中，然后用第二个元素减去第一个元素
的结果作为新序列的第二个元素，再用第三个元素减去第二个元素的结果作为新序
列的第三个元素，以此类推。

*/
int __myfun(int i, int j) { return i * j; }
void test_adjacent_difference()
{
    int arr[5] = {4, 5, 6, 7, 8};
    vector<int> v(arr, arr + 5);

    vector<int> ret(5, 0);
    auto result = adjacent_difference(v.begin(), v.end(), ret.begin());
    for (auto ite = ret.begin(); ite != ret.end(); ite++)
    {
        cout << *ite << " ";
    }
    cout << endl;

    int ret_arr[5] = {0};
    // 使用自定义的二元方法
    adjacent_difference(v.begin(), v.end(), ret_arr, __myfun);
    for (auto i = 0; i < 5; i++)
    {
        cout << ret_arr[i] << " ";
    }
    cout << endl;
}

/*

Test3: inner_product
Header file:  <numeric>
Description: 两个 vector 的内积是对应元素的乘积之和
为了能够得到内积，vector 的长度必须相同

*/
void test_inner_product()
{
    vector<int>v1{1,2,3,4,5};
    vector<int>v2{6,7,8,9,10};
    vector<int>v3{6,7,8,9,10,11};
    vector<int>ret;
    int result = inner_product(v1.begin(),v1.end(), v2.begin(), 0 /* 初始值为0 */);
    cout<<"result = "<<result<<endl;  // 130

    result = inner_product(v1.begin(),v1.end(), v2.begin(), 10 /* 初始值为10 */);
    cout<<"result = "<<result<<endl;  // 140，依据[first, last)的长度截取v2
}

/*

Test4: partial_sum
Header file:  <numeric>
Description: 对于序列 a,b,c,d 产生序列 a,a+b,a+b+c,a+b+c+d

*/
void test_partial_sum()
{
    int arr[5] = {1, 2, 3, 4, 5};
    partial_sum(arr, arr + 5, arr); // 运算结果也放入arr
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " "; // 1 3 6 10 15
    }
    cout << endl;

    adjacent_difference(arr, arr + 5, arr); // 运算结果也放入arr
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " "; // 1 2 3 4 5
    }
    cout << endl;
}

/*

Test5: iota
Header file:  <numeric>
Description: 

*/
void test_iota()
{
    
}

int main(int argc, char* argv[])
{

    // test_accumulate();

    // test_adjacent_difference();

    // test_inner_product();

    test_partial_sum();

    return 0;
}