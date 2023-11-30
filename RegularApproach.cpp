#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

// Function to add an edge to the graph
void addEdge(vector<int> graph[], int u, int v) {
    graph[u].push_back(v);
}


// Function to perform depth-first search (DFS) and calculate path sum recursively
void calculatePathSumUtil(vector<int> graph[], int u, int sumSoFar, int& totalSum) {
    // Add the current vertex value to the sumSoFar
    sumSoFar += u;

    // If the current vertex has no neighbors (leaf node), add its path sum to the totalSum
    if (graph[u].empty()) {
        totalSum += sumSoFar;
        return;
    }

    // Recursively traverse each neighbor of the current vertex
    for (int v : graph[u]) {
        calculatePathSumUtil(graph, v, sumSoFar, totalSum);
    }
}

// Function to calculate path sum in the graph using recursion
int calculatePathSum(vector<int> graph[], int V) {
    int totalSum = 0;

    // Start DFS traversal from every vertex
    for (int i = 0; i < V; ++i) {
        calculatePathSumUtil(graph, i, 0, totalSum);
    }

    return totalSum;
}


void test(int num_nodes, vector<int> &graph, ofstream& csvFile){
    //int pathsum = 0;
    for(int i = 1; i < num_nodes; i++){
        addEdge(&graph,(i-1)/2, i);        
    }                                       
    
    auto startTime = std::chrono::high_resolution_clock::now();
    calculatePathSum(&graph, num_nodes);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>((endTime - startTime)/3.0);
    csvFile << duration.count() << ',';

    for(int i = 0; i < 8; ++i){
        startTime = std::chrono::high_resolution_clock::now();
        calculatePathSum(&graph, num_nodes);
        endTime = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>((endTime - startTime)/3.0);
        csvFile << duration.count() << ',';
        
    }

    startTime = std::chrono::high_resolution_clock::now();
    calculatePathSum(&graph, num_nodes);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>((endTime - startTime)/3.0);
    csvFile << duration.count() << '\n';

}

int main() {

    vector<int> graph1[10];
    vector<int> graph2[100];
    vector<int> graph3[1000];
    vector<int> graph4[10000];
    vector<int> graph5[100000];

    ofstream csvFile;
    csvFile.open("../Regular_data.csv");
    test(10,*graph1,csvFile);
    test(100,*graph2,csvFile);
    test(1000,*graph3,csvFile);
    test(10000,*graph4,csvFile);
    test(100000,*graph5,csvFile);
    csvFile.close();

    return 0;
}
