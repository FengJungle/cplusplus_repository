#ifndef _UNIONFIND_4_H_
#define _UNIONFIND_4_H_

#include <iostream>
#include <cassert>

using namespace std;

// Quick find
namespace UF4{
	class UnionFind{
	private:
		int* parent;
		int* rank; // rank[i]表示以i为根的集合中所表示的树的层数
		int count;
	public:
		UnionFind(int n){
			count = n;
			parent = new int[n];
			rank = new int[n];
			for (int i = 0; i < n; i++){
				parent[i] = i;
				rank[i] = 1;
			}
		}
		~UnionFind(){
			delete[] parent;
			delete[] rank;
		}
		// 查找过程, 查找元素p所对应的集合编号
		// O(h)复杂度, h为树的高度
		int find(int p){
			assert(p >= 0 && p < count);
			while (p != parent[p]){
				parent[p] = parent[parent[p]];// 路径压缩
				p = parent[p];
			}
			return p;
		}
		// 查看元素p和元素q是否所属一个集合
		// O(h)复杂度, h为树的高度
		bool isConnected(int p, int q){
			return find(p) == find(q);
		}
		// 合并元素p和元素q所属的集合
		// O(h)复杂度, h为树的高度
		void unionElements(int p, int q){
			int pRoot = find(p);
			int qRoot = find(q);
			if (pRoot == qRoot){
				return;
			}
			if (rank[pRoot] < rank[qRoot]){
				parent[pRoot] = qRoot;
			}
			else if (rank[pRoot] > rank[qRoot]){
				parent[qRoot] = pRoot;
			}
			else{ // rank相等
				parent[pRoot] = qRoot;//随便加在哪个root上
				rank[qRoot] += 1;
			}
		}
	};
}

#endif // _UNIONFIND_4_H_