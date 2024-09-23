#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

// Function to perform Bellman-Ford algorithm
pair<vector<int>, vector<int>> bellmanFord(const vector<Edge>& edges, int V, int src) {
    vector<int> dist(V, INT_MAX); // Initialize distances to all vertices as infinity
    vector<int> pred(V, -1); // Initialize predecessors to -1
    dist[src] = 0; // Distance to the source is 0

    // Relax all edges V-1 times
    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains a negative weight cycle" << endl;
            return {{}, {}};
        }
    }

    return {dist, pred};
}

// Function to print the shortest path from source to target
void printPath(const vector<int>& pred, int target) {
    if (pred[target] == -1) {
        cout << target;
        return;
    }
    printPath(pred, pred[target]);
    cout << " -> " << target;
}

int main() {
    // Example input: list of edges (src, dest, weight)
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 1}, {1, 3, 1}, {2, 1, 2}, {2, 3, 5}, {3, 4, 3}
    };
    int V = 5; // Number of vertices
    int src = 0; // Source vertex

    auto result = bellmanFord(edges, V, src);
    vector<int> distances = result.first;
    vector<int> predecessors = result.second;

    if (!distances.empty()) {
        cout << "Shortest distances from source vertex " << src << ":" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << ": " << distances[i] << endl;
        }

        cout << "\nPaths from source vertex " << src << ":" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "Path to vertex " << i << ": ";
            printPath(predecessors, i);
            cout << endl;
        }
    }

    return 0;
}