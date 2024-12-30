#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

/*
For Acyclic
5 10
1 2 10
1 3 5
2 4 1
2 3 2
3 2 3
3 4 9
3 5 2
4 5 4
5 4 6
5 1 7

5 10
5 1 7
5 4 6
2 4 1
4 5 4
3 2 3
3 4 9
3 5 2
2 3 2
1 3 5
1 2 10

 */

int node_no, edge_no;       // Number of edges and nodes
vector<int> Node_Vec[100];  // Main Graph
vector<int> Node_Cost[100]; // Graph Weight/Cost
vector<int> nodes;          // d is min cost and pre is previous node
int d[100], pre[100];

void insNode(int node)
{
    if (!nodes.empty())
    {
        for (int u : nodes)
        {
            if (u == node)
            {
                return;
            }
        }
        nodes.push_back(node);
    }
    else
    {
        nodes.push_back(node);
    }
}

void pathPrint(int src)
{
    // Print
    for (int n : nodes)
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

void initializeSingleSource(int src)
{
    // Initialize Single Source

    // cout << "reached initializing for " << src << endl;
    for (int i : nodes)
    {
         // cout << i << " ";
        d[i] = 255; // 255 = inf
        pre[i] = 0; // 0 = Nil
    }
    paragraph;
    d[src] = 0; // Sets source to 0 as the cost will always be 0
    paragraph;
}

void relax(int u)
{
    // Relax
    for (int i = 0; i < Node_Vec[u].size(); i++)
    {
        int v = Node_Vec[u][i];              // v is adjacent node
        cout << u << " " << v << endl << d[u] << " " << Node_Cost[u][i] << " " << d[v] << endl;
        if (d[v] > (d[u] + Node_Cost[u][i])) // checks if the new cost is smaller
        {

            d[v] = d[u] + Node_Cost[u][i]; // Updates cost if smaller
            pre[v] = u;                    // Sets previous node as the currently cycling one
        }

    }
    paragraph;
}

void dijkstra(int src)
{
    initializeSingleSource(src);
    vector<int> S;
    priority_queue<int> Q;
    for (int u : nodes)
    {

        Q.push(-u);
    }
    while(!Q.empty())
    {
        int u = -Q.top();
        Q.pop();
        // cout << u << endl;
        relax(u);
    }
    pathPrint(src);
}

// void DFS(int u)
// {
//     color[u] = GRAY;
//     for (int i = 0; i < Node_Vec[u].size(); i++)
//     {
//         int v = Node_Vec[u][i];
//         if (color[v] == GRAY) // To check if cycle
//         {
//             cycle = true;
//             return;
//         }
//         else if (color[v] == WHITE)
//         {
//             DFS(v);
//         }
//     }
//     color[u] = BLACK;
//     TopS.insert(TopS.begin(), u); // In order to sort topologically, the processed node is to be inserted at first
// }

// void shortestDAG(int src)
// {
//     // Topological Sort
//     for (int i = 1; i <= node_no; i++) // Runs DFS
//     {
//         if (color[i] == WHITE)
//         {
//             DFS(i);
//         }
//     }
//     if (cycle) // Checks if cycle is present
//     {
//         cout << "Cycle Found" << endl;
//         return;
//     }
//     cout << "Topologically Sorted: " << endl;
//     for (int i : TopS)
//     {
//         cout << i << " ";
//     }
//     paragraph;

//     // Cost Update

// }

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
        insNode(nodeA);
        insNode(nodeB);
        Node_Vec[nodeA].push_back(nodeB); // To make it directed
        Node_Cost[nodeA].push_back(cost);
    }
    paragraph;
    cout << "Adjacency List:" << endl;
    for (int i : nodes)
    {
        cout << i << " -> ";
        for (int j = 0; j < Node_Vec[i].size(); j++)
        {
            cout << Node_Vec[i][j] << " (" << Node_Cost[i][j] << "), "; // Node -> Adjacent (Cost)
        }
        paragraph;
    }
    paragraph;
    // for (int i : nodes)
    // {
    //     cout << i << " ";
    // }
    paragraph;

    cout << "Input the source for dijkstra: ";
    int src;
    cin >> src;
    paragraph;

    dijkstra(src);
}
