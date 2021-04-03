#ifndef _UNIONFIND_2_H_
#define _UNIONFIND_2_H_

#include <iostream>
#include <cassert>

using namespace std;

// Quick find
namespace UF2{
	class UnionFind{
	private:
		int* parent;
		int count;
	public:
		UnionFind(int n){
			count = n;
			parent = new int[n];
			for (int i = 0; i < n; i++){
				parent[i] = i;
			}
		}
		~UnionFind(){
			delete[] parent;
		}
		// ���ҹ���, ����Ԫ��p����Ӧ�ļ��ϱ��
		// O(h)���Ӷ�, hΪ���ĸ߶�
		int find(int p){
			assert(p >= 0 && p < count);
			while (p != parent[p]){
				p = parent[p];
			}
			return p;
		}
		// �鿴Ԫ��p��Ԫ��q�Ƿ�����һ������
		// O(h)���Ӷ�, hΪ���ĸ߶�
		bool isConnected(int p, int q){
			return find(p) == find(q);
		}
		// �ϲ�Ԫ��p��Ԫ��q�����ļ���
		// O(h)���Ӷ�, hΪ���ĸ߶�
		void unionElements(int p, int q){
			int pRoot = find(p);
			int qRoot = find(q);
			if (pRoot == qRoot){
				return;
			}
			parent[pRoot] = qRoot;
		}
	};
}

#endif // _UNIONFIND_2_H_