#ifndef _UNIONFIND_1_H_
#define _UNIONFIND_1_H_

#include <iostream>
#include <cassert>

using namespace std;

// Quick find
namespace UF1{
	class UnionFind{
	private:
		int* id;
		int count;
	public:
		UnionFind(int n){
			count = n;
			id = new int[n];
			for (int i = 0; i < n; i++){
				id[i] = i;
			}
		}
		~UnionFind(){
			delete[] id;
		}
		int find(int p){
			assert(p >= 0 && p < count);
			return id[p];
		}
		bool isConnected(int p, int q){
			return find(p) == find(q);
		}

		// 并操作，时间复杂度O(n)
		void unionElements(int p, int q){
			int pId = find(p);
			int qId = find(q);
			if (pId == qId){
				return;
			}
			for (int i = 0; i < count; i++){
				if (id[i] == pId){
					id[i] = qId;
				}
			}
		}
	};
}

#endif // _UNIONFIND_1_H_