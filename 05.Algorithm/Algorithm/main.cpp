#include <iostream>
#include "ShortestPath\ReadGraph.h"
#include "ShortestPath\SparseGraph.h"
#include "ShortestPath\BellmanFord.h"
#include "Sort\CountSort.h"

#include "LinkedList\LlinkedList.h"
#include "Queue\Queue.h"


using namespace std;

#include <vector>

void printInfo(){
	cout << "********************************" << endl;
	cout << "\t\t1----入队------" << endl;
	cout << "\t\t2----出队------" << endl;
	cout << "\t\t3----获取队首元素------" << endl;
	cout << "\t\t4----打印队列------" << endl;
	cout << "\t\t5----退出--------" << endl;
	cout << "********************************" << endl;
	cout << "Input your choice:" << endl;
}

int main()
{
	Queue<int>q(5);
	
	int choice = 0;
	int element = -1;
	printInfo();
	while (1){
		cin >> choice;
		if (choice == 5){
			break;
		}
		switch (choice){
		case 1:
			cout << "input a new element:";
			cin >> element;
			q.enqueue(element);
			break;
		case 2:
			q.dequeue();
			break;
		case 3: 
			cout << q.getFront() << endl;
			break;
		case 4:
			q.print();
			break;
		default:
			break;
		}
		printInfo();
	}

	system("pause");
	return 0;
}