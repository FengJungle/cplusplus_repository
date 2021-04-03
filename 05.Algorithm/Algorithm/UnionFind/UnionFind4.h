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
		int* rank; // rank[i]��ʾ��iΪ���ļ���������ʾ�����Ĳ���
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
		// ���ҹ���, ����Ԫ��p����Ӧ�ļ��ϱ��
		// O(h)���Ӷ�, hΪ���ĸ߶�
		int find(int p){
			assert(p >= 0 && p < count);
			while (p != parent[p]){
				parent[p] = parent[parent[p]];// ·��ѹ��
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
			if (rank[pRoot] < rank[qRoot]){
				parent[pRoot] = qRoot;
			}
			else if (rank[pRoot] > rank[qRoot]){
				parent[qRoot] = pRoot;
			}
			else{ // rank���
				parent[pRoot] = qRoot;//�������ĸ�root��
				rank[qRoot] += 1;
			}
		}
	};
}

#endif // _UNIONFIND_4_H_