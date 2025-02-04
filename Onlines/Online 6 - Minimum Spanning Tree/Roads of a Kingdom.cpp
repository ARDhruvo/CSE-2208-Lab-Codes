#include <bits/stdc++.h>
using namespace std;

/*
 * A Kingdom has 9 villages
 * The King wants to make roads but doesn't want loops or extra cost
 * Print out which roads are unnecessary and should be removed
 */

#define paragraph cout << endl
#define INF 255
#define NIL 0
#define minheap vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>

vector<pair<int, int>> T; // Final Output Set
vector<pair<int, int>> A; // Final Output Set

set<int> Nodes;
priority_queue<pair<int, pair<int, int>>, minheap> Q; // (Cost, (u, v))
set<int> visited;

vector<vector<int>> W;     // Cost Matrix for Adjacency Matrix
vector<vector<int>> Graph; // Ajacent Matrix for

void AdjMatrix(int node)
{
    cout << "\t";
    for (int n : Nodes)
    {
        cout << n << "\t";
    }
    paragraph;

    for (int nodeA : Nodes)
    {
        cout << nodeA << "\t";
        for (int nodeB : Nodes)
        {
            if (W[nodeA][nodeB] != INF)
            {
                cout << W[nodeA][nodeB] << "\t";
            }
            else
            {
                cout << "INF\t";
            }
        }
        paragraph;
    }
}

void Prim(int node_no, int src)
{
    cout << "Required Edges: " << endl;
    int span = 0; // Total cost

    vector<int> weight(node_no, INF); // Initializes all cost to INF
    vector<int> p(node_no, NIL);      // Initalizes all parent node to NIL
    weight[src] = 0;                  // Sets cost of src to 0
    Q.push({0, {src, src}});          // sends the edge of src, src with cost 0 for first initialization

    while (!Q.empty())
    {
        pair<int, pair<int, int>> edge = Q.top(); // edge is the lightest edge
        Q.pop();

        int u = edge.second.second; // Second is taken to avoid src

        if (visited.find(u) != visited.end()) // Checks if u has been worked on before
        {
            A.push_back(edge.second); // If the road is not a safe edge, we add it to the list
            continue;
        }
        visited.insert(u); // u will be worked on this iteration

        if (p[u] != NIL) // Checks for src
        {
            T.push_back(edge.second); // Adds the current edge as one of the required edges
            span += edge.first;       // Adds lightest edge that hasn't been worked on yet
        }

        for (int v : Graph[u])
        {
            if ((visited.find(v) == visited.end()) && (W[u][v] < weight[v])) // If adjacent node has not been visited
            {
                p[v] = u;                  // Update parent node
                weight[v] = W[u][v];       // Update the cost
                Q.push({W[u][v], {u, v}}); // Send in Queue for next calculation
            }
        }
    }
    /*
        cout << "{ ";
        for (pair<int, int> i : T)
        {
            //if()
            cout << "{" << i.first << ", " << i.second << "} ";
        }
        cout << "}";
        paragraph;
        cout << "Cost: " << span << endl;
        paragraph;
    */
    cout << "Removed Roads: ";
    cout << "{ ";
    for (pair<int, int> i : A)
    {
        // if()
        cout << "{" << i.first << ", " << i.second << "} ";
    }
    cout << "}";
    paragraph;
}

int main()
{
    int node_no = 9; // 9 villages
    int edge_no;

    cout << "Enter Number of Roads: ";
    cin >> edge_no;
    node_no++; // As 0 is not counted as a node
    paragraph;

    W.resize(node_no, vector<int>(node_no, INF)); // Initializing cost matrix
    Graph.resize(node_no, vector<int>(node_no));  // Initializing cost matrix
    for (int i = 0; i < node_no; i++)
    {
        W[i][i] = 0; // Cost of visiting a node from itself will always be 0
    }

    int nodeA, nodeB, cost;
    cout << "Enter Connections and Weight:" << endl;
    for (int i = 0; i < edge_no; i++)
    {
        cin >> nodeA >> nodeB >> cost;
        if (nodeA > node_no || nodeB > node_no) // To prevent unnatural numbering
        {
            paragraph;
            cout << "Invalid Node Number" << endl
                 << "Please Enter Node Number within the range of 1 to " << node_no - 1 << endl;
            paragraph;
            i--;
            continue;
        }
        W[nodeA][nodeB] = cost;        // ij-th element of the matrix = cost of visiting j from i
        W[nodeB][nodeA] = cost;        // For undirected graph
        Graph[nodeA].push_back(nodeB); // Sets each the nodes as adjacent nodes
        Graph[nodeB].push_back(nodeA); // As undirected graph
        Nodes.insert(nodeA);
        Nodes.insert(nodeB); // To keep track of total nodes
    }
    paragraph;

    cout << "Adjacency Cost Matrix:" << endl;
    paragraph;
    AdjMatrix(node_no);
    paragraph;

    int src = *Nodes.begin(); // Sends the lowest numbered node as the source for calculations
    Prim(node_no, src);
}
