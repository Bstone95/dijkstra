#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Define the number of vertices in the graph
#define V 6
#define INF INT_MAX // Represents no Connection

// Find minimum distance
int minDistance(int dist[], bool sptSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Print shortest distance
void printSolution(int dist[], int R[]) {
    cout << "Vertex \t Distance from Source \t Next-hop\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            cout << char(i + 'A') << " \t\t " << "INF" << " \t\t " << "-" << endl;
        } else {
            cout << char(i + 'A') << " \t\t " << dist[i] << " \t\t " << char(R[i] + 'A') << endl;
        }
    }
}

// Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];    
    int R[V];       
    bool sptSet[V]; 

    // Create according setup for values
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        R[i] = -1; //next-hop is undefined
    }

    // Source is always 0
    dist[src] = 0;
    R[src] = src; 

    // Vertices excluding source
    for (int count = 0; count < V - 1; count++) {
    
        int u = minDistance(dist, sptSet);

        // Check for any remaining paths or error if no paths
        if (dist[u] == INF) {
            cout << "Error: No path exists to nodes in S. Exiting.\n";
            return;
        }

        // Vertex is now processed
        sptSet[u] = true;

        // Update 
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                R[v] = (R[u] == src) ? v : R[u]; 
            }
        }
    }

    // Print the shortest distances and table
    printSolution(dist, R);
}

int main(){

    int graph [V][V]={
        {INF,2,5,1,INF,INF},
        {2,INF,3,2,INF,INF},
        {5,3,INF,3,1,5},
        {1,2,3,INF,1,INF},
        {INF,INF,1,1,INF,2},
        {INF,INF,5,INF,2,INF}
    };
    dijkstra(graph,0);

    return 0;

}