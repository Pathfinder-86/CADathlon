#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to find the parent of a node (with path compression)
int findParent(int node, vector<int>& parent) {
    if (parent[node] != node) {
        parent[node] = findParent(parent[node], parent);
    }
    return parent[node];
}

// Function to perform the union of two sets
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

// Function to construct the MST using Kruskal's algorithm
vector<Edge> kruskalMST(vector<vector<int>>& edges, int V) {
    vector<Edge> result; // Store the resultant MST
    vector<Edge> edgeList; // Store all edges

    // Convert 2D vector to edge list
    for (const auto& edge : edges) {
        edgeList.push_back({edge[0], edge[1], edge[2]});
    }

    // Sort edges based on their weight
    sort(edgeList.begin(), edgeList.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Initialize parent and rank
    vector<int> parent(V);
    vector<int> rank(V, 0);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    // Iterate through all sorted edges
    for (const auto& edge : edgeList) {
        int u = edge.src;
        int v = edge.dest;

        int setU = findParent(u, parent);
        int setV = findParent(v, parent);

        // If including this edge does not form a cycle
        if (setU != setV) {
            result.push_back(edge);
            unionSets(setU, setV, parent, rank);
        }
    }

    return result;
}

// Function to construct the MST using Prim's algorithm
vector<Edge> primMST(vector<vector<pair<int, int>>>& graph, int V) {
    vector<Edge> result; // Store the resultant MST
    vector<bool> inMST(V, false); // Track vertices included in MST
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap priority queue

    // Start with the first vertex (vertex 0)
    pq.push({0, 0}); // (weight, vertex)

    while (!pq.empty()) {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If the vertex is already in MST, skip it
        if (inMST[u]) continue;

        // Include vertex in MST
        inMST[u] = true;
        result.push_back({u, u, weight});

        // Add all adjacent vertices to the priority queue
        for (const auto& edge : graph[u]) {
            int v = edge.second;
            int w = edge.first;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }

    return result;
}

int main() {
    // Example input for Kruskal's algorithm: 2D vector of edges (src, dest, weight)
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    int V = 4; // Number of vertices

    // Example input for Prim's algorithm: adjacency list of edges (weight, vertex)
    vector<vector<pair<int, int>>> graph = {
        {{10, 1}, {6, 2}, {5, 3}},
        {{10, 0}, {15, 3}},
        {{6, 0}, {4, 3}},
        {{5, 0}, {15, 1}, {4, 2}}
    };

    // Choose which algorithm to run
    cout << "Choose algorithm: 1 for Kruskal, 2 for Prim: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        vector<Edge> mst = kruskalMST(edges, V);
        cout << "Edges in the Minimum Spanning Tree (Kruskal's algorithm):" << endl;
        for (const auto& edge : mst) {
            cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        }
    } else if (choice == 2) {
        vector<Edge> mst = primMST(graph, V);
        cout << "Edges in the Minimum Spanning Tree (Prim's algorithm):" << endl;
        for (const auto& edge : mst) {
            cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}