/*
Shorted Path in Directed Weighted Graph (DAG)

Before:
Adjancency List for Directed Weighted Graph:
unordered_map<int, list<pair<int, int>>> adjList
Algo:
1. Topological Sort 
2. After finding linear ordering, do distance array update

Time Complexity: O(N+E)
Space Complexity: O(N)

DIFF between this and Dijkstras
Type of Graph:

Dijkstra's Algorithm: Can be applied to both directed and undirected graphs with weighted edges.
Topological Sorting with DFS: Specifically designed for directed acyclic graphs (DAGs).
Edge Weights:

Dijkstra's Algorithm: Considers the weights of the edges during the traversal.
Topological Sorting with DFS: Ignores edge weights; it focuses on the structure of the graph.
Data Structures:

Dijkstra's Algorithm: Typically uses a priority queue (min-heap) to efficiently select the node with the minimum distance.
Topological Sorting with DFS: Uses a stack to keep track of the order in which nodes finish processing.
Time Complexity:

Dijkstra's Algorithm: O((V + E) * log(V)), where V is the number of vertices and E is the number of edges.
Topological Sorting with DFS: O(V + E), where V is the number of vertices and E is the number of edges.
*/

#include<bits/stdc++.h>

using namespace std;

void createAdList(unordered_map<int, vector<pair<int, int>>> &adjacencyList, int edges){
    for(int i=0; i<edges; i++){
        cout << "Enter Nodes between edge: ";
        int node1, node2, dis;
        cin >> node1 >> node2;

        cout << "Enter Distance between nodes: ";
        cin >> dis;

        adjacencyList[node1].push_back({node2, dis});
    }
}

void createAdList(unordered_map<int, vector<pair<int, int>>> &adjacencyList, vector<vector<int>> edges){
    for(int i=0; i<edges.size(); i++){
        int node = edges[i][0];
        int node2 = edges[i][1];
        int dis = edges[i][2];
        adjacencyList[node].push_back({node2, dis});
    }
}

void printAdList(unordered_map<int, vector<pair<int, int>>> adjacencyList){
    for(auto s: adjacencyList){
        cout << s.first << ": ";
        for(int i=0; i<s.second.size(); i++){
            cout << "{" << s.second[i].first << "," << s.second[i].second << "}" << " ";
        }
        cout << "\n";
    }
}

void print(vector<int> arr){
    cout << "{ ";
    for(auto i: arr){
        if(i==INT_MAX){
            cout << "INF" << " ";
        }else{
            cout << i << " ";
        }
    }
    cout << "}\n";
}

void dfs(int node, unordered_map<int, vector<pair<int, int>>> adjacencyList, vector<bool> &visited, stack<int> &s){
    visited[node] = true;

    for(auto neigh: adjacencyList[node]){
        if(!visited[neigh.first]){
            dfs(neigh.first, adjacencyList, visited, s);
        }
    }

    s.push(node);
}

stack<int> topologicalSortDFS(unordered_map<int, vector<pair<int, int>>> adjacencyList, int nodes){
    stack<int> s;
    vector<bool> visited(nodes, false);

    for(int i=0; i<nodes; i++){
        if(!visited[i]){
            dfs(i, adjacencyList, visited, s);
        }
    }

    return s;
}

int main(){
    int nodes, edges;
    cout << "Enter Number of Nodes: ";
    cin >> nodes;
    cout << "Enter Number of Edges: ";
    cin >> edges;

    // adjancency list
    unordered_map<int, vector<pair<int, int>>> adjacencyList;
    vector<vector<int>> edgeList = {{0,1,5}, {0,2,3}, {1,2,3}, {1,3,6}, {2,3,7}, {2,4,4}, {2,5,2}, {3,4,-1}, {4,5,-2}};
    // createAdList(adjacencyList, edges);
    createAdList(adjacencyList, edgeList);
    printAdList(adjacencyList);

    // step1: topo sort and find linear stack ordering
    stack<int> linearOrdering = topologicalSortDFS(adjacencyList, nodes);

    // step2: update distance array and output shortest distances
    vector<int> distance(nodes, INT_MAX);
    int src = 1;
    distance[src] = 0;

    // Traverse based on TOPO SORT Ordering
    while(!linearOrdering.empty()){
        int i = linearOrdering.top();
        linearOrdering.pop();
        if(distance[i] != INT_MAX){
            for(auto neighbour: adjacencyList[i]){
                distance[neighbour.first] = min(distance[neighbour.first], distance[i]+neighbour.second);
            }
        }
    }
    cout << "Shortest Distance in DAG from Src: ";
    print(distance);
}