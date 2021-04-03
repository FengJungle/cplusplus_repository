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

	// 所访问的节点是从哪个节点过来的
	int* from;

	void dfs(int v){
		visited[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()){
			if (!visited[i]){
				// i是从v过来的
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

		// 寻路算法
		dfs(s);
	}
	~Path(){
		delete[] visited;
		delete[] from;
	}

	// 从源点s到w是否有路径
	bool hasPath(int w){
		assert(w >= 0 && w < G.V());
		// 如果从s到w有路径，那么dfs过程中一定访问到了，所以visited[w]会置为true，反之为false
		return visited[w];
	}

	// 具体路径（保存在vec中）
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