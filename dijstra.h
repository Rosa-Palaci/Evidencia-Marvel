#include <iostream>
using namespace std;
/*Referencias:
https://www.geeksforgeeks.org/find-the-shortest-distance-between-any-pair-of-two-different-good-nodes/
https://stackoverflow.com/questions/73367093/does-this-line-of-code-do-anything-in-this-dijkstra-algorithm-implementation*/
template <typename T> class Dijkstra {
public:
	int miniDista(int distance[], bool Tset[]){} // finding minimum distance

	int miniDist(vector<int> edges[], int u, int v, int n) {
		// Keep track of visited nodes
		vector<bool> visited(n, 0);
		// Initialize initial distances as 0 for all nodes
		vector<int> distance(n, 0);
		Queue<int> queue;
		distance[u] = 0;
		queue.enqueue(u);
		visited[u] = true;
		while (!queue.empty()) {
			int x = queue.front();
			queue.pop();
			for (int i = 0; i < edges[x].size(); i++) {
				if (visited[edges[x][i]])
					continue;
				// Update the distances
				distance[edges[x][i]] = distance[x] + 1;
				queue.push(edges[x][i]);
				visited[edges[x][i]] = 1;
			}
		}
		return distance[v];
	}
	// Function to add the given edges of the graph
	void add_edge_graph(vector<int> edges[], int u, int v) {
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	vector<T> DijkstraAlgo(Grapho, int src) // adjacency matrix
	{
    vector<T> visitados;
    return visitados;
	}
};