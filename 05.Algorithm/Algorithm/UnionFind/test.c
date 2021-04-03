#include <iostream>
#include "UnionFind\UnionFindTestHelper.h"

using namespace std;

#include <vector>

int main()
{
	int n = 1000000;

	UnionFindTestHelper::testUF3(n);
	UnionFindTestHelper::testUF2(n);
	UnionFindTestHelper::testUF1(n);

	system("pause");
	return 0;
}