#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF 255
#define NIL -1
#define is ==
#define isnt !=

int node_no, edge_no;
vector<int> nodes;

void adjMatrix(vector<vector<int>> W) // Printing Function for the Cost Matrix
{

    cout << "Adjacency Cost Matrix: " << endl
         << endl
         << "\t";
    for (int i = 1; i < node_no; i++)
    {
        cout << i << "    "; // Prints out columns
    }
    paragraph;

    for (int i = 1; i < node_no; i++)
    {
        cout << i << "\t";
        for (int j = 1; j < node_no; j++) // Prints out rows
        {
            if (W[i][j] isnt INF) // Checks if there is connection with j-th node
            {
                cout << W[i][j];
                if ((W[i][j] >= 0) && (W[i][j] < 10)) // Checks negative for spacing reasons
                {
                    cout << "    ";
                }
                else
                {
                    cout << "   "; // Negative numbers get one less space because I have OCD
                }
            }
            else
            {
                cout << "INF  "; // 255 is definied as INF it will not actually print out INF
            }
        }
        paragraph;
    }
    paragraph;
}
void insNode(int node)
{
    if (!nodes.empty())
    {
        for (int u : nodes)
        {
            if (u is node)
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

void pathPrint(vector<int> d, vector<int> pre, int src)
{
    // Print
    for (int n : nodes)
    {
        cout << n << ": ";
        if (d[n] is INF) // Inf means its not possible
        {
            cout << "Not possible" << endl;
        }
        else
        {
            cout << src;
            stack<int> path;
            int x = n;
            while (n isnt src) // Pushes the nodes into the stack until source is found
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

void dijkstra(vector<vector<int>> graph, vector<vector<int>> cost, int src)
{
    vector<int> d(node_no); // d[i] is min cost to reach node i from source
    vector<int> pi(node_no); // pi[i] is immediate predecessor node to reach node i

    // Initialize Single Source:
    for (int i : nodes)
    {
        d[i] = INF; // Sets all the initial cost to reach as INF
        pi[i] = NIL; // Sets all the initial predecessor to NIL
    }
    d[src] = 0; // Sets the cost to reach the source to 0 as it will always be 0 to reach your starting position

    set<int> S; // Set for checking visited nodes
    priority_queue<pair<int, int>> Q; // Takes a priority Queue which takes in pair of (cost to reach node i) and (i)
    // This will help to sort and find the lightest edge from the currently exploring node
    Q.push(make_pair(d[src], src)); // Pushes the (min cost to reach source, source) since the first step starts from source 

    while (!Q.empty()) // Q will be empty once all the nodes have been explored
    {
        int u = Q.top().second; // The second element of the pair is the node to be explored
        Q.pop();

        if (S.find(u) != S.end()) // If node has been visited it will skip
        {
            continue;
        }
        S.insert(u); // Else, insert the node in the visited set

        // Relax
        for (int i = 0; i < graph[u].size(); i++) // For all adjacent nodes of u
        {
            int v = graph[u][i]; // v is the adjacent node of u which updates every iteration
            if (d[v] > (d[u] + cost[u][v])) // If the cost of using source and present node is lower than the previous min cost then it will be updated
            {
                d[v] = (d[u] + cost[u][v]);
                pi[v] = u; // Updates the predecessor to be the currently exploring node
                Q.push(make_pair(-d[v], v)); // Pushes the negative value of the edge with the adjacent node to explore the adjacent node with the lowest value next iteration
                // Negative Value is pushed as priority Queue uses max heap instead of min heap
            }
        }
    }
    paragraph;

    pathPrint(d, pi, src);
}

int main()
{
    cout << "Enter Number of Nodes and Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // Increased for indexing the vector
    paragraph;

    vector<vector<int>> Cost(node_no, vector<int>(node_no, INF)); // The cost matrix is initialized with INF; Assumed at start that all nodes are disconnected
    // This is done for disconnected graphs
    vector<vector<int>> Adj(node_no); // The Adjacent Matrix's i-th vector contains all adjacent nodes of i

    cout << "Enter connections and cost: " << endl;
    int nodeA, nodeB, cost;
    for (int i = 1; i <= edge_no; i++)
    {
        cin >> nodeA >> nodeB >> cost;
        if (cost < 0)
        {
            cout << "Negative Edge Not Allowed.\nPlease Enter Again" << endl;
            i--; // Resets the iteration number by 1 if negative value is entered
            paragraph;
        }
        else
        {
            Cost[nodeA][nodeB] = cost;   // Sets the [i][j]-th element of the matrix to be the cost to visit j from i
            Adj[nodeA].push_back(nodeB); // Updates the Adjacent Matrix
            // Keeps track of all nodes inserted in the graph
            insNode(nodeA);
            insNode(nodeB);
        }
    }
    paragraph;

    adjMatrix(Cost); // Prints the Adjacency Matrix

    int src;
    cout << "Enter source for Dijkstra: ";
    cin >> src;
    paragraph;

    dijkstra(Adj, Cost, src);
}
