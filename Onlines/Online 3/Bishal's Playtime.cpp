#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

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

void pathPrint(int src, int dest, int k)
{
    // Print
    int playtime = k - (2*d[dest]); // Subtracting d[dest] (time spent on the journey) from K (total available time) gives total playtime
    cout << "Playtime = " << playtime << endl << "Path = ";
    if (d[dest] == 255) // Inf means its not possible
    {
        cout << "Not possible" << endl;
    }
    else
    {
        cout << src;
        stack<int> path;
        int x = dest;
        while (dest != src) // Pushes the nodes into the stack until source is found
        {
            path.push(dest);
            dest = pre[dest];
        }
        while (!path.empty()) // Pops them out in sequence for ease of printing
        {
            cout << " -> " << path.top();
            path.pop();
        }
    }
}

void initializeSingleSource(int src)
{
    // Initialize Single Source
    for (int i : nodes)
    {
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
        int v = Node_Vec[u][i]; // v is adjacent node
        if (d[v] > (d[u] + Node_Cost[u][i])) // checks if the new cost is smaller
        {

            d[v] = d[u] + Node_Cost[u][i]; // Updates cost if smaller
            pre[v] = u;                    // Sets previous node as the currently cycling one
        }
    }
}

bool bellman(int src) // Modified Bellman Ford as no negative weight is allowed
{
    initializeSingleSource(src);

    for (int i = 1; i <= node_no; i++) // Bellman gives solution in node - 1 iterations
    {
        for (int u : nodes)
        {
            relax(u); // Does relaxing for all edges to update every time
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
        insNode(nodeA);
        insNode(nodeB);
        Node_Vec[nodeA].push_back(nodeB);
        Node_Vec[nodeB].push_back(nodeA); // To make it bidirected
        Node_Cost[nodeA].push_back(cost);
        Node_Cost[nodeB].push_back(cost); // Pushing cost in both sides as it is bidirected
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

    bellman(1); // Runs modified bellman

    int Q, A, K; // Q = Number of queries, A = Node to visit, K = Total Assigned Time
    cout << "Enter Number of Queries: ";
    cin >> Q;
    cout << "Enter visiting house and assigned time: " << endl;
    for (int i = 0; i < Q; i++)
    {
        cin >> A >> K;
        if((d[A]*2) >= K) // If travel time is twice or more of that of Total Assigned Time, Bishal will not play
        {
            cout << "Will not play" << endl;
        }
        else
        {
            pathPrint(1, A, K);
            paragraph;
        }
    }
}
