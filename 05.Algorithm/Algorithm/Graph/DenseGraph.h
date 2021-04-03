#ifndef _DENSEGRAPH_H_
#define _DENSEGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// ����ͼ - �ڽӾ���
class DenseGraph{
private:
	// ������
	int n;

	// ����
	int m;

	// �Ƿ�������ͼ
	bool directed;

	// �ڽӾ���
	vector<vector<bool>>g;

public:
	DenseGraph(int n, bool directed){
		this->n = n;
		this->m = 0;
		this->directed = directed;
		// n*n ����
		for (int i = 0; i < n; i++){
			g.push_back(vector<bool>(n, false));
		}
	}
	~DenseGraph(){

	}

	// ���ض�����������
	int V(){ return n; }
	int E(){ return m; }

	// �ڶ���v��w֮�����һ����
	void addEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w)){
			return;
		}
		g[v][w] = true;
		if (!directed){
			g[w][v] = true;
		}
		m++;
	}

	// �ж϶���v��w֮���Ƿ����һ����
	bool hasEdge(int v, int w){
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w];
	}

	void show(){
		for (int i = 0; i < n; i++){
			cout << "vertext " << i << "\t";
			for (int j = 0; j < n; j++){
				cout << g[i][j] << "\t";
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
		int begin(){
			index = -1;
			return next();
		}
		int next(){
			for (index += 1; index < G.V(); index++){
				if (G.g[v][index] == true){
					return index;
				}
			}
			return -1;
		}
		bool end(){
			return index >= G.V();
		}
	};
};


#endif // _DENSEGRAPH_H_

// Test
#if 0
int main()
{
	int N = 20;
	int M = 100;

	cout << "\n\n**********************Dense Graph****************" << endl;
	// Dense Graph
	DenseGraph g2(N, false);
	for (int i = 0; i < M; i++){
		int a = rand() % N;
		int b = rand() % N;
		g2.addEdge(a, b);
	}
	// O(V^2)
	for (int v = 0; v < N; v++){
		cout << v << " : ";
		DenseGraph::adjIterator adj(g2, v);
		for (int w = adj.begin(); !adj.end(); w = adj.next()){
			cout << w << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
#endif