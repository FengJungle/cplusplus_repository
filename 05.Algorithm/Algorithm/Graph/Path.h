#ifndef _PATH_H_
#define _PATH_H_

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<typename Graph>
class Path{
private:
	Graph &G;

	// source
	int s;
	bool* visited;

	// �����ʵĽڵ��Ǵ��ĸ��ڵ������
	int* from;

	void dfs(int v){
		visited[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()){
			if (!visited[i]){
				// i�Ǵ�v������
				from[i] = v;
				dfs(i);
			}
		}
	}

public:
	Path(Graph& graph, int s) :G(graph){
		assert(s >= 0 && s < G.V());

		visited = new bool[G.V()];
		from = new int[G.V()];
		for (int i = 0; i < G.V(); i++){
			visited[i] = false;
			from[i] = -1;
		}
		this->s = s;

		// Ѱ·�㷨
		dfs(s);
	}
	~Path(){
		delete[] visited;
		delete[] from;
	}

	// ��Դ��s��w�Ƿ���·��
	bool hasPath(int w){
		assert(w >= 0 && w < G.V());
		// �����s��w��·������ôdfs������һ�����ʵ��ˣ�����visited[w]����Ϊtrue����֮Ϊfalse
		return visited[w];
	}

	// ����·����������vec�У�
	void path(int w, vector<int>&vec){
		stack<int> s;
		int p = w;
		while (p != -1){
			s.push(p);
			p = from[p];
		}

		vec.clear();
		while (!s.empty()){
			vec.push_back(s.top());
			s.pop();
		}
	}

	void showPath(int w){
		vector<int>vec;
		path(w, vec);
		for (int i = 0; i < vec.size(); i++){
			cout << vec[i];
			if (i == vec.size() - 1){
				cout << endl;
			}
			else{
				cout << "-->";
			}
		}
	}
};

#endif // _PATH_H_

#if 0
// Test
int main()
{
	string filename = "testG2.txt";
	SparseGraph g = SparseGraph(6, false);
	ReadGraph<SparseGraph> readGraph1(g, filename);
	g.show();
	cout << endl;

	Path<SparseGraph>dfs(g, 0);
	cout << "DFS : ";
	dfs.showPath(5);
	cout << endl;

	system("pause");
	return 0;
}

#endif 