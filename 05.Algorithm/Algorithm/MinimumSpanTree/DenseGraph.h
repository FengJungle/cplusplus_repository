#ifndef _WEIGHTED_DENSEGRAPH_H_
#define _WEIGHTED_DENSEGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
using namespace std;

// 稠密图 - 邻接矩阵
template<typename Weight>
class DenseGraph{
private:
	// 顶点数
	int n;

	// 边数
	int m;

	// 是否是有向图
	bool directed;

	// 邻接矩阵
	vector<vector<Edge<Weight>* >>g;

public:
	DenseGraph(int n, bool directed){
		this->n = n;
		this->m = 0;
		this->directed = directed;
		// n*n 矩阵
		for (int i = 0; i < n; i++){
			g.push_back(vector<Edge<Weight>*>(n, NULL));
		}
	}
	~DenseGraph(){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (g[i][j] != NULL){
					delete g[i][j];
				}
			}
		}
	}

	// 返回顶点数，边数
	int V(){ return n; }
	int E(){ return m; }

	// 在顶点v和w之间添加一条边
	void addEdge(int v, int w, Weight weight){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		// 重复边，此处的处理为删除后更新
		if (hasEdge(v, w)){
			delete g[v][w];
			if (!directed){
				delete g[v][w];
			}
			m--;
		}
		g[v][w] = new Edge<Weight>(v, w, weight);
		if (!directed){
			g[w][v] = new Edge<Weight>(w, v, weight);
		}
		m++;
	}

	// 判断顶点v和w之间是否存在一条边
	bool hasEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w] != NULL;
	}

	void show(){
		for (int i = 0; i < n; i++){
			cout << "vertext " << i << "\t";
			for (int j = 0; j < n; j++){
				if (g[i][j] != NULL){
					cout << g[i][j]->wt() << "\t";
				}
				else{
					cout << "NULL\t";
				}
			}
			cout << endl;
		}
	}

	class adjIterator{
	private:
		DenseGraph &G;
		int v;
		int index;
	public:
		adjIterator(DenseGraph &graph, int v) :G(graph){
			this->v = v;
			this->index = -1;
		}
		Edge<Weight>* begin(){
			index = -1;
			return next();
		}
		Edge<Weight>* next(){
			for (index += 1; index < G.V(); index++){
				if (G.g[v][index] != NULL){
					return G.g[v][index];
				}
			}
			return NULL;
		}
		bool end(){
			return index >= G.V();
		}
	};
};


#endif // _WEIGHTED_DENSEGRAPH_H_

// Test
#if 0
int main()
{
	string filename = "testG1.txt";
	int V = 8;
	cout << fixed << setprecision(2);

	// 测试带权稠密图
	DenseGraph<double> g1 = DenseGraph<double>(V, false);
	ReadGraph<DenseGraph<double>, double> readGraph1(g1, filename);
	g1.show();
	cout << endl;

	system("pause");
	return 0;
}
#endif