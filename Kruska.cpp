#include <iostream>
#include <algorithm>

using namespace std;

// Class to represent a single edge in the graph
class Edge {
public:
    int sourceVertex, destinationVertex, edgeWeight;

    Edge() : sourceVertex(0), destinationVertex(0), edgeWeight(0) {}
    Edge(int source, int destination, int weight)
        : sourceVertex(source), destinationVertex(destination), edgeWeight(weight) {}
};

// Class to manage Disjoint Set Union (Union-Find)
class DisjointSet {
private:
    int *parent, *rank;
    int size;

public:
    DisjointSet(int totalVertices) {
        size = totalVertices;
        parent = new int[size];
        rank = new int[size];

        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findParent(int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = findParent(parent[vertex]); // Path compression
        }
        return parent[vertex];
    }

    void unionVertices(int vertex1, int vertex2) {
        int root1 = findParent(vertex1);
        int root2 = findParent(vertex2);

        if (root1 != root2) {
            if (rank[root1] < rank[root2])
                parent[root1] = root2;
            else if (rank[root1] > rank[root2])
                parent[root2] = root1;
            else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
};

// Comparator to sort edges by their weights
bool compareEdges(Edge edge1, Edge edge2) {
    return edge1.edgeWeight < edge2.edgeWeight;
}

// Class to compute the MST using Kruskal's Algorithm
class KruskalMST {
public:
    void findMinimumSpanningTree(int totalVertices, int totalEdges, Edge edges[]) {
        sort(edges, edges + totalEdges, compareEdges); // Sort edges by weight

        DisjointSet disjointSet(totalVertices);
        Edge mstEdges[totalVertices - 1]; // To store MST edges
        int mstWeight = 0;
        int edgeCount = 0;

        for (int i = 0; i < totalEdges; i++) {
            if (edgeCount == totalVertices - 1) break;

            int source = edges[i].sourceVertex;
            int destination = edges[i].destinationVertex;

            if (disjointSet.findParent(source) != disjointSet.findParent(destination)) {
                mstEdges[edgeCount++] = edges[i];
                disjointSet.unionVertices(source, destination);
                mstWeight += edges[i].edgeWeight;
            }
        }

        cout << "Edges in the Minimum Spanning Tree (Kruskal's):\n";
        for (int i = 0; i < edgeCount; i++) {
            cout << mstEdges[i].sourceVertex << " -- " << mstEdges[i].destinationVertex
                 << " == " << mstEdges[i].edgeWeight << "\n";
        }
        cout << "Total Weight of MST: " << mstWeight << endl;
    }
};

int main() {
    int totalVertices = 4, totalEdges = 5;
    Edge edges[] = {
        Edge(0, 1, 10),
        Edge(0, 2, 6),
        Edge(0, 3, 5),
        Edge(1, 3, 15),
        Edge(2, 3, 4)
    };

    KruskalMST mst;
    mst.findMinimumSpanningTree(totalVertices, totalEdges, edges);

    return 0;
}
