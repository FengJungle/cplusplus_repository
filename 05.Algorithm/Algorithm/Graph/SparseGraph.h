#ifndef _SPARSEGRAPH_H_
#define _SPARSEGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稀疏图 - 邻接表
class SparseGraph
{
private:
	int n;
	int m;
	bool directed;
	vector<vector<int>>g;
public:
	SparseGraph(int n, bool directed){
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++){
			g.push_back(vector<int>());
		}
	}
	~SparseGraph(){

	}
	// 返回顶点数，边数
	int V(){ return n; }
	int E(){ return m; }

	void addEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(w);
		if (v!=w && !directed){
			g[w].push_back(v);
		}
		m++;
	}
	bool hasEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++){
			if (g[v][i] == w){
				return true;
			}
		}
		return false;
	}

	// 打印
	void show(){
		for (int i = 0; i < n; i++){
			cout << "vertext " << i << "\t";
			for (int j = 0; j < g[i].size(); j++){
				cout << g[i][j] << "\t";
			}
			cout << endl;
		}
	}
	
	// 迭代器
	class adjIterator{
	private:
		SparseGraph &G;
		int v;
		int index;
	public:
		adjIterator(SparseGraph &graph, int v) :G(graph){
			this->v = v;
			index = 0;
		}
		int begin(){
			index = 0;
			if (G.g[v].size()){
				return G.g[v][index];
			}
			return -1;
		}
		int next(){
			index++;
			if (index < G.g[v].size()){
				return G.g[v][index];
			}
			return -1;
		}
		bool end(){
			return index >= G.g[v].size();
		}
	};
};

#endif // _SPARSEGRAPH_H_

// Test

#if 0
int main()
{
	int N = 20;
	int M = 100;

	cout << "\n\n**********************Sparse Graph****************" << endl;
	// Sparse Graph
	SparseGraph g1(N, false);
	for (int i = 0; i < M; i++){
		int a = rand() % N;
		int b = rand() % N;
		g1.addEdge(a, b);
	}

	// O(E)
	for (int v = 0; v < N; v++){
		cout << v << " : ";
		SparseGraph::adjIterator adj(g1, v);
		for (int w = adj.begin(); !adj.end(); w = adj.next()){
			cout << w << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
#endif