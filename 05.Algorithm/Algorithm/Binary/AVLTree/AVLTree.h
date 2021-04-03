#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

using namespace std;
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <assert.h>

template<typename Key, typename Value>
class AVLTree
{
private:
	struct Node{
		Key key;
		Value value;
		int height;
		Node* left;
		Node* right;

		Node(Key key, Value value){
			this->key = key;
			this->value = value;
			this->height = 0;
			this->left = NULL;
			this->right = NULL;
		}
		Node(Node* node){
			this->key = node->key;
			this->value = node->value;
			this->height = node->height;
			this->left = node->left;
			this->right = node->right;
		}
	};
	Node* root;
	int count;
public:
	AVLTree(){
		root = NULL;
		count = 0;
	}
	~AVLTree(){
		if (root != NULL){
			destroy(root);
		}
	}
	int size(){
		return count;
	}
	bool empty(){
		return count == 0;
	}
	vector<Key> preOrder(){
		vector<Key> res;
		stack<Node*>s;
		s.push(root);
		while (!s.empty()){
			Node* cur = s.top();
			s.pop();
			res.push_back(cur->key);
			if (cur->right){
				s.push(cur->right);
			}
			if (cur->left){
				s.push(cur->left);
			}
		}
		return res;
	}
	vector<Key> midOrder(){
		vector<Key>ret;
		stack<Node*>s;
		Node* cur = root;
		while (cur || !s.empty()){
			while (cur != NULL){
				s.push(cur);
				cur = cur->left;
			}
			cur = s.top();
			ret.push_back(cur->key);
			s.pop();
			cur = cur->right;
		}
		return ret;
	}
	vector<Key> postOrder(){
		vector<Key>ret;
		stack<Node*>s, output;
		Node* cur = root;
		while (cur != NULL || !s.empty()){
			if (cur != NULL){
				s.push(cur);
				output.push(cur);
				cur = cur->right;
			}
			else{
				cur = s.top();
				s.pop();
				cur = cur->left;
			}
		}
		while (output.empty() != true){
			Node* node = output.top();
			ret.push_back(node->key);
			output.pop();
		}
		return ret;
	}
	vector<Key> levelOrder(){
		vector<Key>ret;
		queue<Node*>q;
		q.push(root);
		while (!q.empty()){
			Node* node = q.front();
			ret.push_back(node->key);
			q.pop();
			if (node->left){
				q.push(node->left);
			}
			if (node->right){
				q.push(node->right);
			}
		}
		return ret;
	}
	Key maximum(){
		assert(count != 0);
		Node *node = maximum(root);
		return node->key;
	}
	Key minimum(){
		assert(count != 0);
		Node *node = minimum(root);
		return node->key;
	}
	bool contain(Key key){
		return contain(root, key);
	}
	Value* search(Key key){
		Node* node = search(root, key);
		if (node != NULL){
			return &(node->value);
		}
		return NULL;
	}
	int getHeight(){
		return getHeight(root);
	}
	bool isBalanced(){
		return isBalanced(root);
	}
	void add(Key key, Value value){
		root = add(root, key, value);
	}
	void remove(Key key){
		if (root){
			root = remove(root, key);
		}
	}
	void set(Key key, Value value){
		Node* node = get(root, key);
		if (node != NULL){
			node->value = value;
		}
	}
	void printOrder(string des, vector<Key>orderList){
		cout << des << ":\t";
		for (int i = 0; i < orderList.size(); i++){
			cout << orderList[i] << " ";
		}
		cout << endl;
	}
private:
	void destroy(Node* node){
		if (node==NULL){
			return;
		}
		destroy(node->left);
		destroy(node->right);
		delete node;
		count--;
	}
	Node* maximum(Node* node){
		if (node->right == NULL){
			return node;
		}
		return maximum(node->right);
	}
	Node* minimum(Node* node){
		if (node->left == NULL){
			return node;
		}
		return minimum(node->left);
	}
	bool contain(Node* node, Key key){
		if (node == NULL){
			return false;
		}
		if (node->key < key){
			return contain(node->right, key);
		}
		else if (node->key > key){
			return contain(node->left, key);
		}
		return true;
	}
	Node* search(Node* node, Key key){
		if (node == NULL){
			return NULL;
		}
		if (node->key < key){
			return search(node->right, key);
		}
		if (node->key > key){
			return search(node->left, key);
		}
		return node;
	}
	int getHeight(Node* node){
		if (node == NULL){
			return 0;
		}
		return 1 + max(getHeight(node->left), getHeight(node->right));
	}
	int getBalanceFactor(Node* node){
		return getHeight(node->left) - getHeight(node->right);
	}
	bool isBalanced(Node *node){
		if (node == NULL){
			return true;
		}
		int diff = getBalanceFactor(node);
		if (diff > 1 || diff < -1){
			return false;
		}
		return isBalanced(node->left) && isBalanced(node->right);
	}
	Node* leftRotate(Node* node){
		Node* ret = node->right;
		Node* tmp = ret->left;
		ret->left = node;
		node->right = tmp;

		ret->height = 1 + max(getHeight(ret->left), getHeight(ret->right));
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
		return ret;
	}
	Node* rightRotate(Node* node){
		Node* ret = node->left;
		Node* tmp = ret->right;
		ret->right = node;
		node->left = tmp;

		ret->height = 1 + max(getHeight(ret->left), getHeight(ret->right));
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
		return ret;
	}
	Node* add(Node* node, Key key, Value value){
		if (node == NULL){
			cout << "add a new Node: key = " << key << endl;
			count++;
			return new Node(key, value);
		}
		if (node->key < key){
			node->right = add(node->right, key, value);
		}
		else if (node->key > key){
			node->left = add(node->left, key, value);
		}
		else{
			node->value = value;
			cout << "The key and value has existed!" << endl;
			return node;
		}

		node->height = 1 + max(getHeight(node->left), getHeight(node->right));

		int balanceFactor = getBalanceFactor(node);
		if (balanceFactor > 1 && getBalanceFactor(node->left) > 0){
			// LL
			return rightRotate(node);
		}
		if (balanceFactor > 1 && getBalanceFactor(node->left) < 0){
			// LR
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balanceFactor < -1 && getBalanceFactor(node->right) < 0){
			// RR
			return leftRotate(node);
		}
		if (balanceFactor < -1 && getBalanceFactor(node->right) > 0){
			// RL
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}
	Node* remove(Node* node, Key key){
		if (node == NULL){
			return NULL;
		}
		Node* returnNode = node;
		if (node->key < key){
			node->right = remove(node->right, key);
		}
		else if (node->key > key){
			node->left = remove(node->left, key);
		}
		else{
			if (node->left == NULL){
				Node* rightNode = node->right;
				delete node;
				count--;
				returnNode = rightNode;
			}
			else if (node->right == NULL){
				Node* leftNode = node->left;
				delete node;
				count--;
				returnNode = leftNode;
			}
			else{
				cout << "remove a Node: key = " << key << endl;
				Node* successor = new Node(minimum(node->right));
				count++;

				successor->left = node->left;
				successor->right = remove(node->right, successor->key);
				count--;

				returnNode = successor;
			}
		}
		if (returnNode == NULL){
			return NULL;
		}

		returnNode->height = 1 + max(getHeight(returnNode->left), getHeight(returnNode->right));
		int balanceFactor = getBalanceFactor(returnNode);
		if (balanceFactor > 1 && getBalanceFactor(returnNode->left) > 0){
			// LL 
			return rightRotate(returnNode);
		}
		if (balanceFactor > 1 && getBalanceFactor(returnNode->left) < 0){
			// LR 
			returnNode->left = leftRotate(returnNode->left);
			return rightRotate(returnNode);
		}
		if (balanceFactor < -1 && getBalanceFactor(returnNode->right) < 0){
			// RR 
			return leftRotate(returnNode);
		}
		if (balanceFactor < -1 && getBalanceFactor(returnNode->left) > 0){
			// RL 
			returnNode->right = rightRotate(returnNode->right);
			return leftRotate(returnNode);
		}

		return returnNode;
	}
};

bool readFile(string fileName, vector<string>&content){
	// 文件读取
	string line;
	string contents = "";
	ifstream file(fileName);
	if (file.is_open()){
		while (getline(file, line)){
			contents += (line + "\n");
		}
		file.close();
	}
	else{
		cout << "Can not open " << fileName << " !!!" << endl;
		return false;
	}

	// 分割成单词
	const char* s = " ";
	char* src = (char*)contents.c_str();
	char* word = strtok(src, s);
	while (word){
		content.push_back(word);
		word = strtok(NULL, s);
	}

	return true;
}

int  main()
{
	// 测试1

	int arr[6] = { 1, 2, 3, 4, 5, 6};
	AVLTree<int, int> avlTree;
	for (int i = 0; i < 6; i++){
		avlTree.add(i, arr[i]);
	}
	int times = *(avlTree.search(1));
	int t = avlTree.contain(1);


	cout << "Size: " << avlTree.size() << endl;
	cout << "Empty: " << avlTree.empty() << endl;
	cout << "Balanced: " << avlTree.isBalanced() << endl;
	cout << "Minimum: " << avlTree.minimum(); 
	cout << "  value:" << *avlTree.get(avlTree.minimum()) << endl;
	cout << "Maximum: " << avlTree.maximum();
	cout << "  value:" << *avlTree.get(avlTree.maximum()) << endl;
	cout << "Height: " << avlTree.getHeight() << endl;
	vector<int>preOrder = avlTree.levelOrder();
	avlTree.printOrder("preOrder", preOrder);
	cout << *avlTree.get(avlTree.maximum()) << endl;

	avlTree.add(6, 10); 
	cout << "Height: " << avlTree.getHeight() << endl;
	preOrder = avlTree.levelOrder();
	avlTree.printOrder("levelOrder", preOrder);

	// 测试2：读取文本文件，统计单词出现的数量
	vector<string>context;
	bool suc = readFile("test", context);

	AVLTree<string,int>avlTree2;
	for (int i = 0; i < context.size(); i++){
		if (avlTree2.contain(context[i])){
			int times = *(avlTree2.search(context[i]));
			avlTree2.set(context[i], times + 1);
		}
		else{
			avlTree2.add(context[i], 1);
		}
	}
	cout << "Size: " << avlTree2.size() << endl;
	cout << "Empty: " << avlTree2.empty() << endl;
	cout << "Balanced: " << avlTree2.isBalanced() << endl;
	cout << "Minimum: " << avlTree2.minimum() << endl;
	cout << "Maximum: " << avlTree2.maximum() << endl;
	cout << "Height: " << avlTree2.getHeight() << endl;
	cout << "Value: " << *(avlTree2.get("He")) << endl;


	system("pause");
	return 0;
}