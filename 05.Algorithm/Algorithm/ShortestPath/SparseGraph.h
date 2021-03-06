#ifndef _WEIGHTED_SPARSEGRAPH_H_
#define _WEIGHTED_SPARSEGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// ϡ��ͼ - �ڽӱ�
template<typename Weight>
class SparseGraph
{
private:
	int n;
	int m;
	bool directed;
	vector<vector<Edge<Weight>*>>g;
public:
	SparseGraph(int n, bool directed){
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++){
			g.push_back(vector<Edge<Weight>*>());
		}
	}
	~SparseGraph(){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < g[i].size(); j++){
				delete g[i][j];
			}
		}
	}
	// ���ض�����������
	int V(){ return n; }
	int E(){ return m; }

	void addEdge(int v, int w, Weight weight){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(new Edge<Weight>(v, w, weight));
		if (v!=w && !directed){
			g[w].push_back(new Edge<Weight>(w, v, weight));
		}
		m++;
	}
	bool hasEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++){
			if (g[v][i]->other(v) == w){
				return true;
			}
		}
		return false;
	}

	// ��ӡ
	void show(){
		for (int i = 0; i < n; i++){
			cout << "vertext " << i << "\t";
			for (int j = 0; j < g[i].size(); j++){
				cout <<"( to:" << g[i][j]->w()<<",wt:"<<g[i][j]->wt() << ")\t";
			}
			cout << endl;
		}
	}
	
	// ������
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
		Edge<Weight>* begin(){
			index = 0;
			if (G.g[v].size()){
				return G.g[v][index];
			}
			return NULL;
		}
		Edge<Weight>* next(){
			index++;
			if (index < G.g[v].size()){
				return G.g[v][index];
			}
			return NULL;
		}
		bool end(){
			return index >= G.g[v].size();
		}
	};
};

#endif // _WEIGHTED_SPARSEGRAPH_H_

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