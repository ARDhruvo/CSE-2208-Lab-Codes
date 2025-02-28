#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF INT_MAX
#define vertex pair<int, pair<int, vector<vector<int>>>>
#define minheap vertex, vector<vertex>, greater<vertex>

int node_no, edge_no;

vector<int> path;
int finalCost, origSrc;
bool deadEnd = false;

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

int reductionCost(vector<vector<int>> &Cost)
{
    int cost = 0;

    for (int i = 1; i < node_no; i++)
    {
        int red = INF;
        for (int j = 1; j < node_no; j++)
        {
            if (Cost[i][j] < red)
            {
                red = Cost[i][j];
            }
        }
        if (red != INF)
        {

            for (int j = 1; j < node_no; j++)
            {
                if (Cost[i][j] != INF)
                {
                    Cost[i][j] -= red;
                }
            }
            cost += red;
        }
    }

    for (int j = 1; j < node_no; j++)
    {
        int red = INF;
        for (int i = 1; i < node_no; i++)
        {
            if (Cost[i][j] < red)
            {
                red = Cost[i][j];
            }
        }
        if (red != INF)
        {

            for (int i = 1; i < node_no; i++)
            {
                if (Cost[i][j] != INF)
                {
                    Cost[i][j] -= red;
                }
            }
            cost += red;
        }
    }

    return cost;
}

void recurtsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    path.push_back(src);
    vector<int> currPath = path;
    /*
     * for each node v in Nodes:
     * * r = Cost[src][v]
     * * set [src] row Cost to INF
     * * set [v] column Cost to INF
     * * set [src][v] and [v][src] to INF
     * * Cost = r + Reduction of current matrix
     * * Q.push -> {Cost: {v : Current Matrix}}
     */

    // For checking if the currently exploring node is a deadend
    deadEnd = true;
    for (int i : Nodes)
    {
        if (Cost[src][i] != INF)
        {
            deadEnd = false;
            break;
        }
    }
    if (deadEnd)
    {
        if (Nodes.size() > 1)
        {
            path.pop_back();
            return;
        }
        if (Cost[src][origSrc] == INF)
        {
            path.pop_back();
            return;
        }
        else
        {
            deadEnd = false;
        }
    }

    Nodes.erase(src);
    if (Nodes.empty())
    {
        finalCost += Cost[src][origSrc];
        return;
    }
    priority_queue<minheap> Q;
    vector<vector<int>> Dummy(Nodes.size(), vector<int>(node_no, 0));

    for (int v : Nodes)
    {
        int r = Cost[src][v];
        if (r == INF)
        {
            continue;
        }
        Dummy = Cost;
        for (int i = 0; i < node_no; i++)
        {
            Dummy[src][i] = INF;
            Dummy[i][v] = INF;
        }
        Dummy[src][v] = INF;
        Dummy[v][src] = INF;
        int cost = finalCost + reductionCost(Dummy) + r;
        Q.push({cost, {v, Dummy}});
    }

    Dummy = Q.top().second.second;
    finalCost = Q.top().first;
    int nextSrc = Q.top().second.first;
    Q.pop();

    recurtsp(nextSrc, Nodes, Dummy);

    while (deadEnd)
    {
        deadEnd = false;
        if (!Q.empty())
        {
            Dummy = Q.top().second.second;
            finalCost = Q.top().first;
            nextSrc = Q.top().second.first;
            Q.pop();

            recurtsp(nextSrc, Nodes, Dummy);
        }
        else
        {
            deadEnd = true;
            path.pop_back();
            return;
        }
    }

    /*
     * Compare finalCost with the new Q.top()
     * if finalCost is less: win
     * else: I have no idea lol
     */

    while (!Q.empty())
    {
        if (Q.top().first >= finalCost)
        {
            return;
        }
        else
        {
            int origCost = finalCost;
            vector<int> origPath = path;
            path = currPath;

            Dummy = Q.top().second.second;
            finalCost = Q.top().first;
            nextSrc = Q.top().second.first;
            Q.pop();

            recurtsp(nextSrc, Nodes, Dummy);

            if (finalCost >= origCost)
            {
                finalCost = origCost;
                path = origPath;
            }
        }
    }

    if (Q.empty()) // Nothing to do with the current node
    {
        return;
    }
}

void tsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    origSrc = src;

    finalCost = reductionCost(Cost);
    recurtsp(src, Nodes, Cost);

    // For checking if every node can be visited
    if (Nodes.size() != path.size())
    {
        cout << "All nodes cannot be visited" << endl
             << "TSP is not possible";
        return;
    }

    cout << "Path: ";
    for (int i : path)
    {
        cout << i << " -> ";
    }
    cout << src;
    paragraph;

    cout << "Cost: " << finalCost << endl;
}

bool impossible(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    // For checking if graph is disconnected
    if ((node_no - 1) > edge_no)
    {
        cout << "Disconnected Graph" << endl;
        return true;
    }

    // For checking if source is leaf
    for (int i : Nodes)
    {
        if (Cost[src][i] != INF)
        {
            break;
        }
        if ((i == *Nodes.end()) && (Cost[src][i] == INF))
        {
            cout << "Nowhere to go from source" << endl;
            return true;
        }
    }

    // For checking if its possible to return back
    for (int i : Nodes)
    {
        if (Cost[i][src] != INF)
        {
            break;
        }
        if ((i == *Nodes.end()) && (Cost[i][src] == INF))
        {
            cout << "No connection back to source" << endl;
            return true;
        }
    }
    return false;
}

int main()
{
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
        Nodes.insert(nodeA);
        Nodes.insert(nodeB); // To keep track of total nodes
    }
    paragraph;

    AdjMatrix(Nodes, Cost);
    paragraph;

    int src;
    cout << "Enter source for TSP: ";
    cin >> src;
    paragraph;

    if (impossible(src, Nodes, Cost))
    {
        cout << "TSP is not possible" << endl;
    }
    else
    {
        tsp(src, Nodes, Cost);
        paragraph;
    }
}
