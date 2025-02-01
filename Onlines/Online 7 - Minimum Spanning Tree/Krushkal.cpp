#include <bits/stdc++.h>
using namespace std;

/*
7 11
1 2 2
1 7 8
1 6 14
2 3 19
2 6 25
3 6 17
3 4 9
3 5 5
4 5 1
5 6 13
6 7 21
 */

#define paragraph cout << endl
#define INF 255

vector<pair<int, int>> T; // Final Output Set

set<int> Nodes;
priority_queue<pair<int, pair<int, int>>> Edges; // (cost, (u, v))
vector<set<int>> Color;                          // Each index acts as a different color

vector<vector<int>> W; // Cost Matrix for Adjacency Matrix

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

void MakeSet(int v, int i)
{
    Color[i].insert(v); // Each node is set with a different color
}

int FindSet(int v)
{
    for (int i = 0; i < Nodes.size(); i++)
    {
        if (Color[i].find(v) != Color[i].end()) // Searches each color set for the vertex
        {
            return i; // i represents each color so the color of the vertex is returned
        }
    }
}

void Krushkal()
{
    cout << "Required Edges: " << endl;
    int span = 0, node = 0; // Span is the total cost
    for (int v : Nodes)     // Initializes each node with a different color
    {
        MakeSet(v, node);
        node++;
    }

    // For easier and specific calculation later
    pair<int, pair<int, int>> edge;
    int cost;

    while (!Edges.empty())
    {
        edge = Edges.top(); // Takes the edge with the least cost
        cost = -edge.first; // To reverse the negative edge cost that was done for min heap
        Edges.pop();

        // Color of each vertex
        int colorU = FindSet(edge.second.first);
        int colorV = FindSet(edge.second.second);

        if (colorU != colorV) // If the vertices are different colored, tree will be updated
        {
            T.push_back(edge.second); // Sends the edge in the answer set
            span += cost;             // Updates cost

            // The earliest color is assigned so search space is reduced later
            if (colorU > colorV)
            {
                swap(colorU, colorV);
            }

            for (int i : Color[colorV]) // Recolors each vertex in one color with the other
            {
                Color[colorU].insert(i);
            }
        }
    }

    cout << "{ ";
    for (pair<int, int> i : T)
    {
        cout << "{" << i.first << ", " << i.second << "} ";
    }
    cout << "}";
    paragraph;
    cout << "Cost: " << span << endl;
}

int main()
{
    int node_no, edge_no;

    cout << "Enter Number of Nodes and Number of Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // As 0 is not counted as a node
    paragraph;

    W.resize(node_no, vector<int>(node_no, INF)); // Initializing cost matrix
    Color.resize(node_no);                        // Initializing number of colors
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
        W[nodeA][nodeB] = cost; // ij-th element of the matrix = cost of visiting j from i
        W[nodeB][nodeA] = cost; // For undirected graph
        Nodes.insert(nodeA);
        Nodes.insert(nodeB);                                   // To keep track of total nodes
        Edges.push(make_pair(-cost, make_pair(nodeA, nodeB))); // Negative cost with vertices of the edge
    }
    paragraph;

    cout << "Adjacency Matrix:" << endl;
    paragraph;
    AdjMatrix(node_no);
    paragraph;

    Krushkal();
}
