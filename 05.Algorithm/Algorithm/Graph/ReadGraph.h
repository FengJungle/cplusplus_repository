#ifndef _READGRAPH_H_
#define _READGRAPH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>

using namespace std;

template<typename Graph>
class ReadGraph{
public:
	ReadGraph(Graph &graph, const string &filename){
		ifstream file(filename);
		string line;
		int V, E;

		assert(file.is_open());

		assert(getline(file, line));
		stringstream ss(line);
		ss >> V >> E;

		// 读取的顶点数量和图的顶点数量一致
		assert(V == graph.V());
		for (int i = 0; i < E; i++){
			assert(getline(file, line));
			stringstream ss(line);

			int a, b;
			ss >> a >> b;
			assert(a < V && a >= 0);
			assert(b < V && b >= 0);
			graph.addEdge(a, b);
		}
	}
};

#endif // _READGRAPH_H_

// Test 

#if 0
int main()
{
	string filename = "testG1.txt";

	SparseGraph g1(13, false);
	ReadGraph<SparseGraph> readGraph1(g1, filename);
	cout << "test G1 in Sparse Graph:" << endl;
	g1.show();
	cout << endl;

	DenseGraph g2(13, false);
	ReadGraph<DenseGraph> readGraph2(g2, filename);
	cout << "test G1 in Sparse Graph:" << endl;
	g2.show();
	cout << endl;

	system("pause");
	return 0;
}
#endif
