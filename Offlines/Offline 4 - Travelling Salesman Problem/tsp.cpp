#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF INT_MAX
#define vertex pair<int, pair<int, vector<vector<int>>>>
#define minheap vertex, vector<vertex>, greater<vertex>

vector<int> path;

void AdjMatrix(set<int> Nodes, vector<vector<int>> W)
{
    cout << "Adjacency Matrix:" << endl;
    paragraph;
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

void tsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    path.push_back(src);
    priority_queue<minheap> Q;

    /*
     * Reduction
     * for each node v in Nodes:
     * * r = Cost[src][v]
     * * set [src] row Cost to INF
     * * set [v] column Cost to INF
     * * set [src][v] and [v][src] to INF
     * * Cost = r + Reduction of current matrix
     * * Q.push -> {Cost: {v : Current Matrix}}
     */
}

int main()
{
    int node_no, edge_no;

    cout << "Enter Number of Nodes and Number of Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // As 0 is not counted as a node
    paragraph;

    set<int> Nodes;
    vector<vector<int>> Cost(node_no, vector<int>(node_no, INF));
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
        Cost[nodeA][nodeB] = cost; // ij-th element of the matrix = cost of visiting j from i
        // W[nodeB][nodeA] = cost; // For undirected graph
        Nodes.insert(nodeA);
        Nodes.insert(nodeB); // To keep track of total nodes
        // Edges.push(make_pair(-cost, make_pair(nodeA, nodeB))); // Negative cost with vertices of the edge
    }
    paragraph;

    AdjMatrix(Nodes, Cost);
    paragraph;

    int src;
    cout << "Enter source for TSP: ";
    cin >> src;
    Nodes.erase(src);
    tsp(src, Nodes, Cost);
    paragraph;
}
