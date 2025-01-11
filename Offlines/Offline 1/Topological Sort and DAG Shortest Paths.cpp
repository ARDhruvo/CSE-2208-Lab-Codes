#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define WHITE -1
#define GRAY 0
#define BLACK 1

/*
For Acyclic
6 9
2 4 -3
3 4 1
3 5 2
4 6 6
5 6 4
2 3 -2
2 6 5
4 5 -5
3 6 5

For Cyclic:
6 9
2 4 -3
3 4 1
3 5 2
4 6 6
5 6 4
2 3 -2
2 6 5
4 5 -5
6 3 5
 */

int node_no, edge_no; // Number of edges and nodes
bool cycle = false; // To check if Acyclic Graph
vector<int> Node_Vec[100]; // Main Graph
vector<int> Node_Cost[100]; // Graph Weight/Cost
vector<int> TopS; // Topologically sorted nodes
int color[12]; // depends on the size of input

void DFS(int u)
{
    color[u] = GRAY;
    for (int i = 0; i < Node_Vec[u].size(); i++)
    {
        int v = Node_Vec[u][i];
        if (color[v] == GRAY) // To check if cycle
        {
            cycle = true;
            return;
        }
        else if (color[v] == WHITE)
        {
            DFS(v);
        }
    }
    color[u] = BLACK;
    TopS.insert(TopS.begin(), u); // In order to sort topologically, the processed node is to be inserted at first
}

void shortestDAG(int src)
{
    // Topological Sort
    for (int i = 1; i <= node_no; i++) // Runs DFS 
    {
        if (color[i] == WHITE)
        {
            DFS(i);
        }
    }
    if (cycle) // Checks if cycle is present
    {
        cout << "Cycle Found" << endl;
        return;
    }
    cout << "Topologically Sorted: " << endl;
    for (int i : TopS)
    {
        cout << i << " ";
    }
    paragraph;

    // Initialize Single Source
    int d[100], pre[100]; // d is min cost and pre is previous node
    for (int i : TopS)
    {
        d[i] = 255; // 255 = inf
        pre[i] = 0; // 0 = Nil
    }
    d[src] = 0; // Sets source to 0 as the cost will always be 0
    paragraph;

    // Cost Update
    for (int u : TopS)
    {
        for (int i = 0; i < Node_Vec[u].size(); i++)
        {
            int v = Node_Vec[u][i]; // v is adjacent node
            // Relax
            if (d[v] > (d[u] + Node_Cost[u][i])) // checks if the new cost is smaller
            {
                d[v] = d[u] + Node_Cost[u][i]; // Updates cost if smaller
                pre[v] = u; // Sets previous node as the currently cycling one
            }
        }
    }

    // Print
    for (int n : TopS)
    {
        cout << n << ": ";
        if (d[n] == 255) // Inf means its not possible
        {
            cout << "Not possible" << endl;
        }
        else
        {
            cout << src;
            stack<int> path;
            int x = n;
            while (n != src) // Pushes the nodes into the stack until source is found
            {
                path.push(n);
                n = pre[n];
            }
            while (!path.empty()) // Pops them out in sequence for ease of printing
            {
                cout << " -> " << path.top();
                path.pop();
            }
            cout << " Cost: " << d[x] << endl;
        }
    }
}

int main()
{
    cout << "Enter Number of Nodes and Edges: ";
    cin >> node_no >> edge_no;
    paragraph;

    cout << "Enter connections and cost:" << endl;
    for (int i = 0; i < edge_no; i++)
    {
        int nodeA, nodeB, cost;
        cin >> nodeA >> nodeB >> cost;
        Node_Vec[nodeA].push_back(nodeB); // To make it directed
        Node_Cost[nodeA].push_back(cost);
    }
    paragraph;
    cout << "Adjacency List:" << endl;
    for (int i = 1; i <= node_no; i++)
    {
        cout << i << " -> ";
        for (int j = 0; j < Node_Vec[i].size(); j++)
        {
            cout << Node_Vec[i][j] << " (" << Node_Cost[i][j] << "), "; // Node -> Adjacent (Cost)
        }
        paragraph;
    }
    for (int i = 1; i <= node_no; i++) // Initializes all nodes to white for DFS
    {
        color[i] = WHITE;
    }
    paragraph;

    cout << "Input the source for edge relaxation: ";
    int src;
    cin >> src;
    paragraph;

    shortestDAG(src);
}
