#ifndef _LINKED_LIST_
#define _LINKED_LIST_

template<typename Element>
class LinkedList{
private:
	struct Node{
		Element e;
		Node* next;

		Node(Element e, Node* next){
			this->e = e;
			this->next = next;
		}
		Node(Node *node){
			this->e = node->e;
			this->next = node->next;
		}
		Node(){
			this(NULL, NULL);
		}
	};

	int count;
	Node* head;
public:
	LinkedList(){
		this->count = 0;
		this->head = NULL;
	}
	~LinkedList(){
		if (head != NULL){
			Node* p = head;
			while (p != NULL){
				Node* temp = p;
				p = p->next;
				delete temp;
				count--;
			}
		}
	}
	int size(){
		return count;
	}
	bool empty(){
		return count == 0;
	}

	void insert(Element e){
		if (head == NULL){
			head = new Node(e, NULL);
			count++;
		}
		else{
			Node* p = head;
			while (p->next != NULL){
				p = p->next;
			}
			p->next = new Node(e, NULL);
			count++;
		}
	}
	// É¾³ýÔªËØ
	void remove(Element e){
		if (count > 0){
			if (find(e) == -1){
				cout << "no such elment" << endl;
				return;
			}
			if (head->e == e){
				Node* temp = head;
				head = head->next;
				delete temp;
				count--;
			}
			else{
				Node* pre = head;
				Node* p = head;
				while (p->e != e){
					pre = p;
					p = p->next;
				}
				pre->next = p->next;
				delete p;
				count--;
			}
		}
	}
	int find(Element e){
		assert(count > 0);
		int index = 0;

		Node* p = head;
		while (p != NULL && p->e != e){
			p = p->next;
			index++;
		}
		if (p == NULL){
			return -1;
		}
		return index;
	}
	void printList(){
		if (count == 0){
			cout << "Empty list" << endl;
			return;
		}
		Node *p = head;
		while (p->next != NULL){
			cout << p->e << " --> ";
			p = p->next;
		}
		cout << p->e << endl;
	}
	void destroy(){
		if (head != NULL){
			Node* p = head;
			while (p != NULL){
				Node* tmp = p->next;
				delete p;
				count--;
				p = tmp;
			}
			head = NULL;
		}
	}
};


#endif // _LINKED_LIST_

#if 0

void printInfo(){
	cout << "********************************" << endl;
	cout << "\t\t1----²åÈëÔªËØ------" << endl;
	cout << "\t\t2----É¾³ýÔªËØ------" << endl;
	cout << "\t\t3----É¾³ýÁ´±í------" << endl;
	cout << "\t\t4----´òÓ¡Á´±í------" << endl;
	cout << "\t\t5------ÍË³ö--------" << endl;
	cout << "********************************" << endl;
	cout << "Input your choice:" << endl;
}

int main()
{
	LinkedList<int>list;

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
			list.insert(element);
			break;
		case 2:
			cout << "input the element you want to delete:";
			cin >> element;
			list.remove(element);
			break;
		case 3:
			list.destroy();
			break;
		case 4:
			list.printList();
			break;
		default:
			break;
		}
		printInfo();
	}

	system("pause");
	return 0;
}

#endif