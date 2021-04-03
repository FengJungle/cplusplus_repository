#ifndef _LAZY_PRIM_MST_H_
#define _LAZY_PRIM_MST_H_

#include "MinHeap.h"

template<typename Graph, typename Weight>
class LazyPrimMST{
private:
	Graph& G;
	MinHeap<Edge<Weight>>pq;// 优先队列
	bool *marked; // 点是否被标记
	vector<Edge<Weight>>mst;
	Weight mstWeight; 

	void visit(int v){
		assert(!marked[v]);
		marked[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
			if (!marked[e->other(v)]){
				pq.insert(*e);// 潜在的横切边
			}
		}
	}
public:
	LazyPrimMST(Graph& g) :G(g), pq(MinHeap<Edge<Weight>>(g.E())){
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); i++){
			marked[i] = false;
		}
		mst.clear();

		// Lazt Prim
		visit(0);
		while (!pq.empty()){
			Edge<Weight> e = pq.extractMin();
			if (marked[e.v()] == marked[e.w()]){
				// 同色，不是横切边
				continue;
			}
			mst.push_back(e);
			if (!marked[e.v()]){
				visit(e.v());
			}
			else{
				visit(e.w());
			}
		}
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); i++){
			mstWeight += mst[i].wt();
		}
	}
	~LazyPrimMST(){
		delete[]marked;
	}
	vector<Edge<Weight>> mstEdges(){
		return mst;
	}
	Weight result(){
		return mstWeight;
	}
};

#endif // _LAZY_PRIM_MST_H_

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
	cout << "Test Lazy Prim MST: " << endl;
	LazyPrimMST<SparseGraph<double>, double> lazyPrimMST(g);
	vector<Edge<double>>mst = lazyPrimMST.mstEdges();
	for (int i = 0; i < mst.size(); i++){
		cout << mst[i] << endl;
	}
	cout << "The MST weight is: " << lazyPrimMST.result() << endl;

	cout << endl;
	system("pause");
	return 0;
}

#endif
