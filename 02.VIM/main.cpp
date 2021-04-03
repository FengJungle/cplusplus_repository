#include <iostream>
using namespace std;

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

int main()
{
	cout<<"Hello World!"<<endl;

	int a = 0;
	int b = 0;
	int choice = 0;
	while(1)
	{
		cout<<"Input number a = ";cin>>a;
		cout<<"Input number b = ";cin>>b;
		cout<<"Input your choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"a + b = "<<add(a, b)<<endl;
				break;
			case 2:
				cout<<"a - b = "<<sub(a, b)<<endl;
				break;
			case 3:
				cout<<"a * b = "<<mul(a, b)<<endl;
				break;
			case 4:
				cout<<"a / b = "<<div(a, b)<<endl;
				break;
			default:
				cout<<"quit"<<endl;
		}
		if(choice > 4 || choice < 1)
		{
			break;
		}
	}
	cout<<"Goodbye!"<<endl;

	return 0;
}
