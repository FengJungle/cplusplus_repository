#include <iostream>
using namespace std;

class Base {
public:
	Base() {
		cout << "Base::Base()" << endl;
		a = 1;
		b = 2;
	}
	void func_1() {
		cout << "Base::func_1()" << endl;
	}
	virtual void func_2() {
		cout << "Base::func_2()" << endl;
	}
	virtual void func_3() {
		cout << "Base::func_3()" << endl;
	}
	~Base() {
		cout << "Base::~Base()" << endl;
	}

private:
	int a;
	int b;
};

class Base2 : public Base {
public:
	Base2() {
		c = 3;
		d = 4;
	}
	virtual void func_4() {
		cout << "Base2::func_4()" << endl;
	};
	virtual void func_5() {
		cout << "Base2::func_5()" << endl;
	};
private:
	int c;
	int d;
};

class Base3 :public Base {
public: 
	Base3() {
		e = 5;
		f = 6;
	}
	// 覆写func_3
	virtual void func_3() {
		cout << "Base3::func_3()" << endl;
	};
	virtual void func_6() {
		cout << "Base3::func_6()" << endl;
	};
private:
	int e;
	int f;
};

class Father1 {
public:
	Father1() {
		x = 111;
	}
	virtual void func_1() {
		cout << "Father1::func_1()" << endl;
	}
private:
	int x;
};

class Father2 {
public:
	Father2() {
		y = 222;
	}
	virtual void func_2() {
		cout << "Father2::func_2()" << endl;
	}
private:
	int y;
};

class Child :public Father1, public Father2 {
public:
	Child() {
		z = 333;
	}
	virtual void func_3() {
		cout << "Child::func_3()" << endl;
	}
private:
	int z;
};


/*
*  Function name: Test1
*  Description  : 测试类的虚函数表，类中包括两个虚函数
*                 1. Print size of object base;
*                 2. Print member of object base;
*                 3. Get the address of virtual function and call it, which proves the existence of virtual function table.
*  Return       ： None
*/
void Test1()
{
	Base base;
	Base* pBase = &base;
	cout << "base Size: " << sizeof(base) << endl;

	// 虚函数表地址放在对象开始处
	printf("虚函数表地址： 0x%x\n", *(int*)pBase);
	// 然后才存放其他成员变量
	printf("%d\n", *(int*)((int*)pBase + 1));
	printf("%d\n", *(int*)((int*)pBase + 2));

	typedef void(*pFunc)();
	pFunc fun;

	for (int i = 0; i < 2; i++) {
		fun = (pFunc)*((int*)(*(int*)pBase) + i);
		fun();
	}
}

/*
*  Function name: Test2
*  Description  : 测试继承类的虚函数表，基类中包括两个虚函数，派生类中包含两个虚函数，且不覆写
*                 1. Print size of object base2;
*                 2. Print member of object base2;
*                 3. Get the address of virtual function and call it, which proves the existence of virtual function table.
*  Return       ： None
*/
void Test2()
{
	Base2 base2;
	Base2* pBase2 = &base2;
	cout << "base2 Size : " << sizeof(base2) << endl;

	// 虚函数表地址放在对象开始处
	printf("虚函数表地址：0x%x\n", *(int*)(pBase2));
	// 然后存放其他成员变量
	printf("%d\n", *(int*)((int*)pBase2 + 1));
	printf("%d\n", *(int*)((int*)pBase2 + 2));
	printf("%d\n", *(int*)((int*)pBase2 + 3));
	printf("%d\n", *(int*)((int*)pBase2 + 4));

	// 取出虚函数
	typedef void(*pFunc)();
	pFunc fun;

	/*
	*     Base :: virtual func_2
	*     Base :: virtual func_3
	*     Base2:: virtual func_4
	*     Base2:: virtual func_5
	*/
	for (int i = 0; i < 4; i++) {
		fun = (pFunc)*(((int*)*(int*)pBase2) + i);
		fun();
	}
}

/*
*  Function name: Test3
*  Description  : 测试继承类的虚函数表，基类中包括两个虚函数，派生类中包含两个虚函数，覆写基类的其中一个虚函数
*                 1. Print size of object base3;
*                 2. Print member of object base3;
*                 3. Get the address of virtual function and call it, which proves the existence of virtual function table.
*  Return       ： None
*/
void Test3()
{
	Base3 base3;
	Base3* pBase3 = &base3;
	cout << "base3 Size : " << sizeof(base3) << endl;

	// 虚函数表地址放在对象开始处
	printf("虚函数表地址：0x%x\n", *(int*)pBase3);
	// 然后存放其他成员变量
	printf("%d\n", *((int*)pBase3 + 1));
	printf("%d\n", *((int*)pBase3 + 2));
	printf("%d\n", *((int*)pBase3 + 3));
	printf("%d\n", *((int*)pBase3 + 4));

	typedef void(*pFunc)();
	pFunc fun;

	/*
	*     Base :: virtual func_2
	*     Base3:: virtual func_3
	*     Base3:: virtual func_6
	*/
	for (int i = 0; i < 3; i++) {
		fun = (pFunc)*(((int*)*(int*)pBase3) + i);
		fun();
	}
}

/*
*  Function name: Test4
*  Description  : 测试继承类的虚函数表，类Child有两个父类Father1和Father2
*                 1. Print size of object Child;
*                 2. Print member of object Child;
*                 3. Get the address of virtual function and call it, which proves the existence of virtual function table.
*  Return       ： None
*/
void Test4()
{
	Child child;
	Child* pChild = &child;
	cout << "child Size : " << sizeof(child) << endl;

	// 虚函数表地址放在对象开始处
	printf("虚函数表 1 地址：0x%x\n", *(int*)pChild);
	printf("虚函数表 2 地址：0x%x\n", *((int*)pChild + 2));
	// 然后存放其他成员变量
	printf("%d\n", *((int*)pChild + 1));
	printf("%d\n", *((int*)pChild + 3));
	printf("%d\n", *((int*)pChild + 4));

	typedef void(*pFunc)();
	pFunc fun;

	/*
	*     Father1 :: virtual func_1
	*     Child:: virtual func_3
	*/
	for (int i = 0; i < 2; i++) {
		fun = (pFunc)*(((int*)*(int*)pChild) + i);
		fun();
	}

	/*
	*     Father2 :: virtual func_2
	*/
	for (int i = 0; i < 1; i++) {
		fun = (pFunc)*(((int*)*((int*)pChild + 2)) + i);
		fun();
	}
}

int main()
{
	Test4();

	return 0;
}