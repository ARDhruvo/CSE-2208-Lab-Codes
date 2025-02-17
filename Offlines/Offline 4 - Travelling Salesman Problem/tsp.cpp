#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF INT_MAX
#define vertex pair<int, pair<int, vector<vector<int>>>>
#define minheap vertex, vector<vertex>, greater<vertex>

int node_no, edge_no;

vector<int> path;
int finalCost;

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
}

void recurtsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    /*
     * for each node v in Nodes:
     * * r = Cost[src][v]
     * * set [src] row Cost to INF
     * * set [v] column Cost to INF
     * * set [src][v] and [v][src] to INF
     * * Cost = r + Reduction of current matrix
     * * Q.push -> {Cost: {v : Current Matrix}}
     */

    if (!Nodes.empty())
    {
        Nodes.erase(src);
        path.push_back(src);
        priority_queue<minheap> Q;
        vector<vector<int>> Dummy(Nodes.size(), vector<int>(node_no, 0));
        int dummIndex = 0;

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
        finalCost = Q.top().second.first;
        int nextSrc = Q.top().first;
        Q.pop();

        recurtsp(nextSrc, Nodes, Dummy);

        /*
         * Compare finalCost with the new Q.top()
         * if finalCost is less: win
         * else: I have no idea lol
         */
    }
}

void tsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    finalCost = reductionCost(Cost);
    recurtsp(src, Nodes, Cost);
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
    tsp(src, Nodes, Cost);
    paragraph;
}
