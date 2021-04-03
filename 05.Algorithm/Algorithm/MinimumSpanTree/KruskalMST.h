#ifndef _KRUSKAL_MST_H_
#define _KRUSKAL_MST_H_

#include "MinHeap.h"
#include "UnionFind.h"
#include <iostream>
#include <vector>
using namespace std;


template<typename Graph, typename Weight>
class KruskalMST{
private:
	vector<Edge<Weight>>mst;
	Weight mstWeight;
public:
	KruskalMST(Graph& graph){
		// ¶ÑÅÅÐò£ºÅÅÐòËùÓÐµÄ±ß
		MinHeap<Edge<Weight>>pq(graph.E());
		for (int i = 0; i < graph.V(); i++){
			typename Graph::adjIterator adj(graph, i);
			for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
				if (e->v()>e.w()){
					pq.insert(*e);
				}
			}
		}

		UnionFind uf(graph.V());
		while (!pq.empty() && mst.size() < graph.V() - 1){
			Edeg<Weight>e = pq.extractMin();
			if (uf.isConnected(e.v(), e.w())){
				continue;
			}
			mst.push_back(e);
			uf.unionElements(e.v(), e.w());
		}
		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); i++){
			mstWeight += mst[i].wt();
		}
	}
	~KruskalMST(){

	}
	Weight result(){
		return mstWeight;
	}
	vector<Edge<Weight>> mstEdges(){
		return mstWeight;
	}
};

#endif