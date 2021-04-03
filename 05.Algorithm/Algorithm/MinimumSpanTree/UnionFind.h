#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_

#include <iostream>
#include <cassert>

class UnionFind{
private:
	int* parent;
	int* rank;
	int count;
public:
	UnionFind(int count){
		parent = new int[count];
		rank = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++){
			parent[i] = i;
			rank[i] = 1;
		}
	}
	~UnionFind(){
		delete[] parent;
		delete[] rank;
	}

	int find(int p){
		//assert(p >= 0 && p < count);
		while (p != parent[p]){
			parent[p] = parent[parent[p]];//Â·¾¶Ñ¹Ëõ
			p = parent[p];
		}
		return p;
	}
	bool isConnected(int p, int q){
		return find(p) == find(q);
	}
	void unionElements(int p, int q){
		int rootP = find(p);
		int rootQ = find(q);

		if (rootP == rootQ){
			return;
		}

		if (rank[rootP] < rank[rootQ]){
			parent[rootP] = rootQ;
		}
		else if (rank[rootP] > rank[rootQ]){
			parent[rootQ] = rootP;
		}
		else{
			parent[rootQ] = rootP;
			rank[rootQ] += 1;
		}
	}
};

#endif