#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

// Function to perform BFS and find an augmenting path
bool bfs(const vector<vector<int>>& residualGraph, int src, int sink, vector<int>& parent) {
    int V = residualGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(src);
    visited[src] = true;
    parent[src] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

// Function to implement the Ford-Fulkerson algorithm using the Edmonds-Karp method
int fordFulkerson(vector<vector<int>>& graph, int src, int sink) {
    int V = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(V);
    int maxFlow = 0;

    // Augment the flow while there is a path from source to sink
    while (bfs(residualGraph, src, sink, parent)) {
        // Find the maximum flow through the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to the overall flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Example input: adjacency matrix of the graph
    vector<vector<int>> graph = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    int src = 0; // Source vertex
    int sink = 5; // Sink vertex

    cout << "The maximum possible flow is " << fordFulkerson(graph, src, sink) << endl;

    return 0;
}