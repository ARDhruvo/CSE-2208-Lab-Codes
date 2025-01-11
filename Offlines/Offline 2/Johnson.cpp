#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF 255
#define NIL -1
#define is ==
#define isnt !=

/*
Input from Slide
5 9
1 2 3
1 3 8
1 5 -4
5 4 6
4 1 2
4 3 -5
3 2 4
2 5 7
2 4 1

Input from GFG
4 5
1 2 -5
2 3 4
1 3 2
3 4 1
1 4 3
 */

int node_no, edge_no;          // Globally declared for using everywhere
vector<vector<int>> Cost, Adj; // Cost Matrix and Adjoint Matrix to keep track of weight and adjacent nodes respectively
vector<vector<int>> D, Pi;     // D and Pi are the final Cost and Predecessor Matrix
vector<vector<int>> Wn;        // Vector for Modified Weight W' (and lambda' later)
bool negEdge = false;          // Initially assumes negative edge cycle is absent
vector<int> h;                 // Vector for h(u)

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

void preMatrix(vector<vector<int>> W) // Printing Function for the Predecessor Matrix
{
    cout << "Adjacency Predecessor Matrix: " << endl
         << endl
         << "\t";
    for (int i = 1; i < node_no; i++)
    {
        cout << i << "    "; // Prints out the columns
    }
    paragraph;
    for (int i = 1; i < node_no; i++) // Prints out the rows
    {
        cout << i << "\t";
        for (int j = 1; j < node_no; j++)
        {
            if (W[i][j] != NIL) // Checks if there is a connection with the j-th node
            {
                cout << W[i][j] << "    ";
            }
            else
            {
                cout << "NIL  "; // 0 is definied as NIL, it will not actually print out NIL
            }
        }
        paragraph;
    }
    paragraph;
}

void bellman(int src)
{
    // Initializes Single Source
    vector<int> d(node_no, INF);
    vector<int> pi(node_no, NIL); // pi[i] is immediate predecessor node to reach node i
    d[src] = 0;

    h.resize(node_no); // Resizing h to the size of node_no

    for (int i = 1; i <= node_no; i++) // Bellman gives solution in node - 1 iterations
    {
        for (int u = 0; u < node_no; u++) // u starts from 0 as it is the newly added node
        {
            for (int v : Adj[u]) // For all adjacent nodes of u
            {
                if (d[v] > (d[u] + Cost[u][v])) // If the cost of using source and present node is lower than the previous min cost then it will be updated
                {
                    d[v] = (d[u] + Cost[u][v]);
                    pi[v] = u; // Updates the predecessor to be the currently exploring node
                }
                h[v] = d[v]; // Sets all h(v) = lambda(s, v)
            }
        }
    }

    // For checking Negative Edge Cycle
    for (int u = 1; u < node_no; u++)
    {
        for (int i = 0; i < Adj[u].size(); i++) // For all adjacent nodes of u
        {
            int v = Adj[u][i];              // v is the adjacent node of u which updates every iteration
            if (h[v] > (h[u] + Cost[u][v])) // If the cost of using source and present node is lower than the previous min cost then there is a negative edge cycle
            {
                negEdge = true;
                cout << "There is a Negative Edge Cycle" << endl;
                return;
            }
        }
    }
    paragraph;
}

void dijkstra(int src)
{
    // Initializes Single Source
    vector<int> d(node_no, INF);   // d[i] is min cost to reach node i from source
    vector<int> pre(node_no, NIL); // pi[i] is immediate predecessor node to reach node i
    d[src] = 0;                    // Sets the cost to reach the source to 0 as it will always be 0 to reach your starting position

    set<int> S;                       // Set for checking visited nodes
    priority_queue<pair<int, int>> Q; // Takes a priority Queue which takes in pair of (cost to reach node i) and (i)
    // This will help to sort and find the lightest edge from the currently exploring node
    Q.push(make_pair(0, src)); // Pushes the (min cost to reach source, source) since the first step starts from source

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
        for (int v : Adj[u])              // For all adjacent nodes of u
        {                                 // v is the adjacent node of u which updates every iteration
            if (d[v] > (d[u] + Wn[u][v])) // If the cost of using source and present node is lower than the previous min cost then it will be updated
            {
                d[v] = (d[u] + Wn[u][v]);
                pre[v] = u;                  // Updates the predecessor to be the currently exploring node
                Q.push(make_pair(-d[v], v)); // Pushes the negative value of the edge with the adjacent node to explore the adjacent node with the lowest value next iteration
                // Negative Value is pushed as priority Queue uses max heap instead of min heap
            }
        }
    }
    Wn[src] = d;   // Updates the source's W' to the new distance
    Pi[src] = pre; // Updates the source's Predecessor Matrix
}

void printPath(int i, int j) // Recursive print path from i to j
{
    // The basic principle is that it will explore from the destination to the source by going
    // through the predecessor node
    // If the predecessor node is NIL, there will be no way to reach j from i
    // Else, it will recursively check the predecessor node until it reaches the source
    if (i == j) // Starts from i
    {
        cout << i;
    }
    else if (Pi[i][j] == NIL) // If the predecessor of any node is NIL, it will imply that at no point was the predecessor updated and hence there is no way to visit j from i
    {
        cout << "No path from " << i << " to " << j << " exists" << endl;
        return;
    }
    else
    {
        printPath(i, Pi[i][j]); // Recursively reaches the source and then goes back to the immediate after node until reaching the destination
        cout << " -> " << j;
    }
}

void Johnson()
{
    // Adds 0 as the new temp node
    int new_src = 0;
    for (int i = 1; i < node_no; i++)
    {
        Cost[0][i] = 0;      // Sets cost from 0 to all nodes as 0
        Adj[0].push_back(i); // COnnects all nodes with 0
    }

    // Runs Bellman Ford with 0 as the source
    bellman(new_src);
    if (negEdge) // If there is a negative cycle it will break
    {
        cout << "There is no solution to the graph" << endl;
        return;
    }

    // Initializing Wn as the Modified weight graph
    Wn.resize(node_no, vector<int>(node_no, INF));
    for (int i = 1; i < node_no; i++)
    {
        Wn[i][i] = 0; // Self looping prevention thing
    }
    for (int u = 1; u < node_no; u++)
    {
        for (int v : Adj[u])
        {
            Wn[u][v] = Cost[u][v] + h[u] - h[v]; // Updates each element using W' = W(u,v) + h(v) - h(u)
        }
    }

    // Runs Dijkstra using all nodes
    for (new_src = 1; new_src < node_no; new_src++)
    {
        dijkstra(new_src);
    }

    // Initializes D = d(u,v) as a new node_no x node_no matrix
    D.resize(node_no, vector<int>(node_no, INF));
    for (int i = 1; i < node_no; i++)
    {
        D[i][i] = 0; // Self looping prevention thing
    }

    // Updates d(u,v) for the final time
    for (int u = 1; u < node_no; u++)
    {
        for (int v = 1; v < node_no; v++)
        {
            if ((D[u][v] = Wn[u][v] + h[v] - h[u]) <= (INF - 20))
            {
                D[u][v] = Wn[u][v] + h[v] - h[u]; // Updates each element as d(u,v) = lambda(u,v) + h(v) - h(u)
            }
            else
            {
                D[u][v] = INF; // For printing purposes
            }
        }
    }

    cout << "Johnson completed ";
    adjMatrix(D);  // Prints the finally obtained Cost Matrix
    cout << "Johnson completed ";
    preMatrix(Pi); // Prints the finally obtained Predecessor Matrix

    for (int i = 1; i < node_no; i++) // Prints ALL path
    {
        cout << "From " << i << " to " << endl;
        for (int j = 1; j < node_no; j++)
        {
            cout << j << ": ";
            printPath(i, j);
            if (D[i][j] isnt INF)
            {
                cout << "   Cost: " << D[i][j] << endl;
            }
        }
        paragraph;
    }
}

int main()
{
    cout << "Enter Number of Nodes and Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // Increased for indexing the vector
    paragraph;

    Cost.resize(node_no, vector<int>(node_no, INF)); // The cost matrix is initialized with INF; Assumed at start that all nodes are disconnected
    // This is done for disconnected graphs
    for (int i = 1; i < node_no; i++)
    {
        Cost[i][i] = 0; // Sets the cost of each node to itself to 0 to prevent Self Loop
    }
    Adj.resize(node_no);                           // The Adjacent Matrix's i-th vector contains all adjacent nodes of i
    Pi.resize(node_no, vector<int>(node_no, NIL)); // Sets the Predecessor matrix to NIL until input

    cout << "Enter connections and cost: " << endl;
    int nodeA, nodeB, cost;
    for (int i = 1; i <= edge_no; i++)
    {
        cin >> nodeA >> nodeB >> cost;
        Cost[nodeA][nodeB] = cost;   // Sets the [i][j]-th element of the matrix to be the cost to visit j from i
        Pi[nodeA][nodeB] = nodeA;    // Sets the [i] as [j]'s predecessor
        Adj[nodeA].push_back(nodeB); // Updates the Adjacent Matrix
    }
    paragraph;

    adjMatrix(Cost); // Prints the input Cost Matrix
    preMatrix(Pi);   // Prints the input Adjacent Matrix
    paragraph;

    Johnson();
}
