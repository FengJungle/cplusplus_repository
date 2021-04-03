#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Edge.h"
#include "IndexMinHeap.h"
#include <vector>
#include <stack>

using namespace std;

// Dijkstra��Դ���·���㷨�����ͼ�����и�Ȩ��
// ���Ӷȣ�O(Elog(V))
template<typename Graph, typename Weight>
class Dijkstra{
private:
	Graph& G;
	int s;// source
	// Դ�㵽ÿһ����������·��ֵ
	Weight* distTo;
	bool* marked;

	// Դ�㵽ÿ����������·��
	vector<Edge<Weight>*>from;
public:
	Dijkstra(Graph& graph, int s):G(graph){
		this->s = s;
		marked = new bool[G.V()];
		distTo = new Weight[G.V()];
		for (int i = 0; i < G.V(); i++){
			distTo[i] = Weight();
			marked[i] = false;
			from.push_back(NULL);
		}

		IndexMinHeap<Weight>ipq(G.V());

		// Dijkstra
		distTo[s] = Weight();//0
		marked[s] = true;
		from[s] = new Edge<Weight>(s, s, Weight());
		ipq.insert(s, distTo[s]);
		while (!ipq.empty()){
			int v = ipq.extractMinIndex();
			// distTo[v]���Ǵ�Դ��s��v����̾���
			marked[v] = true;
			typename Graph::adjIterator adj(G, v);
			for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
				int w = e->other(v);
				if (!marked[w]){
					if (from[w] == NULL || distTo[v] +e->wt() < distTo[w]){
						distTo[w] = distTo[v] + e->wt();
						from[w] = e;
						if (ipq.contain(w)){
							ipq.change(w, distTo[w]);
						}
						else{
							ipq.insert(w, distTo[w]);
						}
					}
				}
			}
		}
	}
	~Dijkstra(){
		delete[]marked;
		delete[]distTo;
		delete from[0];
	}
	Weight shortestPathTo(int w){
		return distTo[w];
	}
	bool hasPathTo(int w){
		return marked[w];
	}
	void shortestPath(int w, vector<Edge<Weight>>&vec){
		stack<Edge<Weight>*>s;
		Edge<Weight> *e = from[w];
		while (e->v() != e->w()){
			s.push(e);
			e = from[e->v()];
		}
		while (!s.empty()){
			e = s.top();
			s.pop();
			vec.push_back(*e);
		}
	}
	void showPath(int w){
		assert(w >= 0 && w < G.V());
		vector<Edge<Weight>>vec;
		shortestPath(w, vec);
		for (int i = 0; i < vec.size(); i++){
			cout << vec[i].v() << " -> ";
			if (i == vec.size() - 1){
				cout << vec[i].w() << endl;
			}
		}
	}
};

#endif // _DIJKSTRA_H

#if 0

int main()
{
	string filename = "testG1.txt";
	int V = 5;
	cout << fixed << setprecision(2);

	// ���Դ�Ȩϡ��ͼ
	SparseGraph<int> g = SparseGraph<int>(V, false);
	ReadGraph<SparseGraph<int>, int> readGraph(g, filename);
	g.show();
	cout << endl;

	// ������С������
	cout << "Test Dijkstra: " << endl;
	Dijkstra<SparseGraph<int>, int>dij(g, 0);
	for (int i = 1; i < V; i++){
		cout << "Shortest Path to " << i << " : " << dij.shortestPathTo(i) << endl;
		dij.showPath(i);
		cout << "---------------" << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

#endif 
