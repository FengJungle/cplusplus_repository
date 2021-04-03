#ifndef _BELLMANFORD_H_
#define _BELLMANFORD_H_

#include <vector>
#include <stack>
#include "Edge.h"

// BellmanFord单源最短路径算法
// 图中不能有负权环
// 复杂度 O(EV)
template<typename Graph, typename Weight>
class BellmanFord{
private:
	Graph& G;
	int s;
	Weight* distTo;
	vector<Edge<Weight>*>from;
	// 是否有负权环
	bool hasNegativeCycle;

	// 进行第V次松弛操作，如果还有优化，则说明有负权环
	bool detectNegativeCycle(){
		for (int i = 0; i < G.V(); i++){
			typename Graph::adjIterator adj(G, i);
			for (Edge<Weight>*e = adj.begin(); !adj.end(); e = adj.next()){
				if (from[e->v()] && distTo[e->v()] + e->wt() < distTo[e->w()]){
					return true;
				}
			}
		}
		return false;
	}
public:
	BellmanFord(Graph& graph, int s) :G(graph){
		this->s = s;
		distTo = new Weight[G.V()];
		// 初始化所有的节点s都不可达, 由from数组来表示
		for (int i = 0; i < G.V(); i++){
			from.push_back(NULL);
		}

		// 设置distTo[s] = 0, 并且让from[s]不为NULL, 表示初始s节点可达且距离为0
		distTo[s] = Weight();
		from[s] = new Edge<Weight>(s, s, Weight()); // 这里我们from[s]的内容是new出来的, 注意要在析构函数里delete掉

		// BellmanFord
		for (int pass = 1; pass < G.V(); pass++){
			for (int i = 0; i < G.V(); i++){
				typename Graph::adjIterator adj(G, i);
				for (Edge<Weight>*e = adj.begin(); !adj.end(); e = adj.next()){
					if (from[e->v()] && (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])){
						distTo[e->w()] = distTo[e->v()] + e->wt();
						from[e->w()] = e;
					}
				}
			}
		}
		hasNegativeCycle = detectNegativeCycle();
	}
	~BellmanFord(){
		delete[]distTo;
		delete from[s];
	}

	bool negativeCycle(){
		return this->hasNegativeCycle;
	}
	Weight shortestPathTo(int w){
		return distTo[w];
	}
	bool hasPathTo(int w){
		return from[w] != NULL;
	}
	void shortestPath(int w, vector<Edge<Weight>>&vec){
		assert(!hasNegativeCycle);
		assert(w >= 0 && w < G.V());
		stack<Edge<Weight>*>s;
		Edge<Weight> *e = from[w];
		while (e->v() != this->s){
			s.push(e);
			e = from[e->v()];
		}
		while (!s.empty()){
			vec.push_back(*(s.top));
			s.pop();
		}
	}
	void showPath(int w){
		assert(!hasNegativeCycle);
		assert(w >= 0 && w < G.V());
		vector<Edge<Weight>>vec;
		shortestPath(w, vec);
		for (int i = 0; i < vec.size(); i++){
			cout << vec[i].v() << " -> ";
			if (i = vec.size() - 1){
				cout << vec[i].w() << endl;
			}
		}
	}
};

#endif