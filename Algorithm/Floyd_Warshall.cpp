#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Function to perform Floyd-Warshall algorithm
pair<vector<vector<int>>, vector<vector<int>>> floydWarshall(const vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph; // Initialize distance matrix with the input graph
    vector<vector<int>> parent(V, vector<int>(V, -1)); // Initialize parent matrix

    // Initialize parent matrix
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] != INF && i != j) {
                parent[i][j] = i;
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    return {dist, parent};
}

// Function to print the shortest path from source to target
void printPath(const vector<vector<int>>& parent, int src, int target) {
    if (src == target) {
        cout << src;
        return;
    }
    if (parent[src][target] == -1) {
        cout << "No path";
        return;
    }
    vector<int> path;
    int current = target;
    while (current != src) {
        path.push_back(current);
        current = parent[src][current];
    }
    path.push_back(src);
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i != 0) {
            cout << " -> ";
        }
    }
}

int main() {
    // Example input: adjacency matrix of the graph
    vector<vector<int>> graph = {
        {0, 4, 1, INF, INF},
        {INF, 0, INF, 1, INF},
        {INF, 2, 0, 5, INF},
        {INF, INF, INF, 0, 3},
        {INF, INF, INF, INF, 0}
    };
    int V = 5; // Number of vertices

    auto result = floydWarshall(graph, V);
    vector<vector<int>> distances = result.first;
    vector<vector<int>> parents = result.second;

    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (distances[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << distances[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "\nPaths between every pair of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << "Path from " << i << " to " << j << ": ";
            printPath(parents, i, j);
            cout << endl;
        }
    }

    return 0;
}