#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> Edge; // (weight, vertex)

// Function to perform Dijkstra's algorithm
pair<vector<int>, vector<int>> dijkstra(const vector<vector<Edge>>& graph, int V, int src) {
    vector<int> dist(V, INT_MAX); // Initialize distances to all vertices as infinity
    vector<int> pred(V, -1); // Initialize predecessors to -1
    vector<bool> visited(V, false); // Initialize visited array to false
    dist[src] = 0; // Distance to the source is 0

    // Min-heap priority queue to store vertices based on their current shortest distance
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, src}); // (distance, vertex)

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // If the vertex is already visited, skip it
        if (visited[u]) continue;
        visited[u] = true;

        // Iterate through all adjacent vertices of u
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // If there is a shorter path to v through u
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u; // Record the predecessor
                pq.push({dist[v], v});
            }
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
    // Example input: adjacency list of edges (vertex, weight)
    vector<vector<Edge>> graph = {
        {{1, 4}, {2, 1}},        // Edges from vertex 0
        {{3, 1}},                // Edges from vertex 1
        {{1, 2}, {3, 5}},        // Edges from vertex 2
        {{4, 3}},                // Edges from vertex 3
        {}                       // Edges from vertex 4 (no outgoing edges)
    };
    int V = 5; // Number of vertices
    int src = 0; // Source vertex

    auto result = dijkstra(graph, V, src);
    vector<int> distances = result.first;
    vector<int> predecessors = result.second;

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

    return 0;
}