#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF INT_MAX

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

int main()
{
    int node_no, edge_no;

    cout << "Enter Number of Nodes and Number of Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // As 0 is not counted as a node
    paragraph;

    set<int> Nodes;
    vector<vector<int>> Cost(node_no);
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
}