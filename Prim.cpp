#include <iostream>
#include <climits>

using namespace std;

class PrimMST {
private:
    int totalVertices;

public:
    PrimMST(int vertices) : totalVertices(vertices) {}

    void findMinimumSpanningTree(int adjacencyMatrix[5][5]) {
        int parentVertex[totalVertices];   // To store the MST
        int minimumEdgeWeight[totalVertices]; // Smallest edge weight to connect a vertex
        bool isVertexIncluded[totalVertices]; // Tracks vertices included in the MST

        for (int i = 0; i < totalVertices; i++) {
            minimumEdgeWeight[i] = INT_MAX;
            isVertexIncluded[i] = false;
        }

        minimumEdgeWeight[0] = 0;     // Start from vertex 0
        parentVertex[0] = -1;         // Root node of the MST

        for (int vertexCount = 0; vertexCount < totalVertices - 1; vertexCount++) {
            int minWeightVertex = -1;

            // Find the vertex with the smallest edge weight
            for (int i = 0; i < totalVertices; i++) {
                if (!isVertexIncluded[i] && 
                    (minWeightVertex == -1 || minimumEdgeWeight[i] < minimumEdgeWeight[minWeightVertex])) {
                    minWeightVertex = i;
                }
            }

            isVertexIncluded[minWeightVertex] = true;

            // Update adjacent vertices
            for (int adjacentVertex = 0; adjacentVertex < totalVertices; adjacentVertex++) {
                if (adjacencyMatrix[minWeightVertex][adjacentVertex] &&
                    !isVertexIncluded[adjacentVertex] &&
                    adjacencyMatrix[minWeightVertex][adjacentVertex] < minimumEdgeWeight[adjacentVertex]) {
                    minimumEdgeWeight[adjacentVertex] = adjacencyMatrix[minWeightVertex][adjacentVertex];
                    parentVertex[adjacentVertex] = minWeightVertex;
                }
            }
        }

        cout << "Edges in the Minimum Spanning Tree (Prim's):\n";
        int totalMSTWeight = 0;
        for (int i = 1; i < totalVertices; i++) {
            cout << parentVertex[i] << " -- " << i << " == " 
                 << adjacencyMatrix[i][parentVertex[i]] << "\n";
            totalMSTWeight += adjacencyMatrix[i][parentVertex[i]];
        }
        cout << "Total Weight of MST: " << totalMSTWeight << endl;
    }
};

int main() {
    int totalVertices = 5;
    int adjacencyMatrix[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    PrimMST prim(totalVertices);
    prim.findMinimumSpanningTree(adjacencyMatrix);

    return 0;
}
