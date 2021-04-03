#ifndef _PRIM_MST_H_
#define _PRIM_MST_H_

#include <vector>
#include "Edge.h"
#include "IndexMinHeap.h"

template<typename Graph, typename Weight>
class PrimMST{
private:
	bool* marked;
	IndexMinHeap<Weight>ipq;     // 存权值
	vector<Edge<Weight>*>edgeTo; // 存边
	Graph& g;
	vector<Edge<Weight>>mst;
	Weight mstWeight;	

	void visit(int v){
		if (marked[v] == true)return;
		marked[v] = true;

		typename Graph::adjIterator adj(g, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
			int w = e->other(v);
			if (!marked[w]){
				if (!edgeTo[w]){
					ipq.insert(w, e->wt());
					edgeTo[w] = e;
				}
				else if (e->wt() < edgeTo[w]->wt()){
					ipq.change(w, e->wt());
					edgeTo[w] = e;
				}
			}
		}
	}

public:
	PrimMST(Graph& G) :g(G), ipq(IndexMinHeap<Weight>(G.V())){
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); i++){
			marked[i] = false;
			edgeTo.push_back(NULL);
		}
		mst.clear();

		visit(0);
		while (!ipq.empty()){
			int v = ipq.extractMinIndex();
			assert(edgeTo[v]);
			mst.push_back(*edgeTo[v]);
			visit(v);
		}

		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); i++){
			mstWeight += mst[i].wt();
		}
	}
	
	Weight result(){
		return mstWeight;
	}

	vector<Edge<Weight>> mstEdges(){
		return mst;
	}
}

#endif // _PRIM_MST_H_

#if 0

int main()
{
	string filename = "testG1.txt";
	int V = 8;
	cout << fixed << setprecision(2);

	// 测试带权稀疏图
	SparseGraph<double> g = SparseGraph<double>(V, false);
	ReadGraph<SparseGraph<double>, double> readGraph(g, filename);
	g.show();
	cout << endl;

	// 测试最小生成树
	cout << "Test Prim MST: " << endl;
	PrimMST<SparseGraph<double>, double> PrimMST(g);
	vector<Edge<double>>mst2 = PrimMST.mstEdges();
	for (int i = 0; i < mst2.size(); i++){
		cout << mst2[i] << endl;
	}
	cout << "The MST weight is: " << PrimMST.result() << endl;

	cout << endl;
	system("pause");
	return 0;
}

#endif