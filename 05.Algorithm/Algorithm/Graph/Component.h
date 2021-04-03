#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>
#include <assert.h>

using namespace std;

template<typename Graph>
class Component{
private:
	Graph &G;
	// 标记是否被访问过
	bool *visited;
	// 连通分量数量
	int ccount;

	// 相连的节点id相同
	int *id;

	void dfs(int v){
		visited[v] = true;
		id[v] = ccount;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()){
			if (!visited[i]){
				dfs(i);
			}
		}
	}
public:
	Component(Graph& graph) :G(graph){
		visited = new bool[G.V()];
		id = new int[G.V()];
		ccount = 0;
		for (int i = 0; i < G.V(); i++){
			visited[i] = false;
			id[i] = -1;
		}

		for (int i = 0; i < G.V(); i++){
			if (!visited[i]){
				// 深度优先遍历
				dfs(i);
				ccount++;
			}
		}
	}
	~Component(){
		delete[] visited;
		delete[] id;
	}
	// 连通分量
	int count(){
		return ccount;
	}
	bool isConnected(int v, int w){
		assert(v >= 0 && v < G.V());
		assert(w >= 0 && w < G.V());
		return id[v] == id[w];
	}
};

#endif // _COMPONENT_H_