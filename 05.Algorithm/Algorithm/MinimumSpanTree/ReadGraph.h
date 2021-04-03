#ifndef _READ_WEIGHTED_GRAPH_H_
#define _READ_WEIGHTED_GRAPH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>

using namespace std;

template<typename Graph, typename Weight>
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
			Weight w;
			ss >> a >> b >> w;
			assert(a < V && a >= 0);
			assert(b < V && b >= 0);
			graph.addEdge(a, b, w);
		}
	}
};

#endif // _READ_WEIGHTED_GRAPH_H_

// Test 

#if 0
int main()
{
	string filename = "testG1.txt";
	int V = 8;
	cout << fixed << setprecision(2);

	// 测试带权稀疏图
	SparseGraph<double> g2 = SparseGraph<double>(V, false);
	ReadGraph<SparseGraph<double>, double> readGraph2(g2, filename);
	g2.show();
	cout << endl;


	system("pause");
	return 0;
}
#endif
