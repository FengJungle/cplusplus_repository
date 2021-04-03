#ifndef _SHORTESTPATH_H_
#define _SHORTESTPATH_H_

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


template<typename Graph>
class ShortestPath{
private:
	Graph& G;
	int s;
	bool *visited;
	int *from;
	// 记录从s到每一个节点的最短距离
	int *order;
public:
	ShortestPath(Graph &g, int s) :G(g){
		assert(s >= 0 && s < G.V());

		visited = new bool[G.V()];
		from = new int[G.V()];
		order = new int[G.V()];
		for (int i = 0; i < G.V(); i++){
			visited[i] = false;
			from[i] = -1;
			order[i] = -1;
		}
		this->s = s;

		queue<int>q;

		// 无向图最短路径算法
		// 广度优先遍历
		q.push(s);
		visited[s] = true;
		order[s] = 0;
		while (!q.empty()){
			int v = q.front();
			q.pop();
			
			typename Graph::adjIterator adj(G, v);
			for (int i = adj.begin(); !adj.end(); i = adj.next()){
				if (!visited[i]){
					q.push(i);
					from[i] = v;
					visited[i] = true;
					order[i] = order[v] + 1;
				}
			}
		}
	}
	~ShortestPath(){
		delete[] visited;
		delete[] from;
		delete[] order;
	}

	bool hasPath(int w){
		assert(w >= 0 && w < G.V());
		return visited[w];
	}
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
		assert(w >= 0 && w < G.V());
		vector<int> vec;
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
	int length(int w){
		assert(w >= 0 && w < G.V());
		return order[w];
	}
};

#endif // _SHORTESTPATH_H_

#if 0

int main()
{
	string filename = "testG2.txt";
	SparseGraph g = SparseGraph(6, false);
	ReadGraph<SparseGraph> readGraph1(g, filename);
	g.show();
	cout << endl;

	ShortestPath<SparseGraph>bfs(g, 0);
	cout << "BFS : ";
	bfs.showPath(5);
	cout << endl;

	system("pause");
	return 0;
}

#endif