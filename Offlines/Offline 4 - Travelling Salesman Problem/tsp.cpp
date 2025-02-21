#include <bits/stdc++.h>
using namespace std;

/*
5 20
1 2 20
1 3 30
1 4 10
1 5 11
2 1 15
2 3 16
2 4 4
2 5 2
3 1 3
3 2 5
3 4 2
3 5 4
4 1 19
4 2 6
4 3 18
4 5 3
5 1 16
5 2 4
5 3 7
5 4 16

5 11
1 2 9
2 3 4
3 2 3
3 4 4
4 3 7
4 2 6
1 4 8
4 5 12
5 4 10
5 1 1
2 5 2

5 11
1 2 9
2 3 6
3 2 3
3 4 4
4 3 8
4 2 6
1 4 8
4 5 13
5 4 10
5 1 1
2 5 4

4 6
1 2 1
4 1 4
2 3 3
2 4 2
4 3 3
3 4 3
 */

#define paragraph cout << endl
#define INF INT_MAX
#define vertex pair<int, pair<int, vector<vector<int>>>>
#define minheap vertex, vector<vertex>, greater<vertex>

int node_no, edge_no;

vector<int> path;
vector<bool> inPath;
int finalCost, origSrc;
bool deadEnd = false, unreachable = false;

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

void pathPrint()
{
    paragraph;
    for (int i : path)
    {
        cout << i << " -> ";
    }
    paragraph;
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
        // cout << "Current Source: " << src << ": " << finalCost << endl;
        Nodes.erase(src);
        path.push_back(src);
        inPath[src] = true;
        if (Nodes.empty())
        {
            if (Cost[src][origSrc] != INF)
            {
                finalCost += Cost[src][origSrc];
            }
            else
            {
                cout << "Unreachable from " << src << endl;
                cout << "Explored path: ";
                for (int i : path)
                {
                    cout << i << " ";
                }
                paragraph;
                unreachable = true;
                Nodes.insert(src);
                inPath[src] = false;
                paragraph;
            }
            return;
        }
        priority_queue<minheap> Q;
        vector<vector<int>> Dummy(Nodes.size(), vector<int>(node_no, 0));

        for (int v : Nodes)
        {
            cout << "Exploring: " << src << " " << v << endl;
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
            pathPrint();
            AdjMatrix(Nodes, Dummy);
            paragraph;
            Q.push({cost, {v, Dummy}});
        }

        if (Q.empty())
        {
            cout << "Third Check" << endl;
            deadEnd = true;
            // path.pop_back();
            return;
        }

        Dummy = Q.top().second.second;
        finalCost = Q.top().first;
        int nextSrc = Q.top().second.first;
        Q.pop();

        recurtsp(nextSrc, Nodes, Dummy);

        // CHECKS

        if (unreachable)
        {
            if (Nodes.size() < 2)
            {
                path.pop_back();
                return;
            }

            Dummy = Q.top().second.second;
            finalCost = Q.top().first;
            nextSrc = Q.top().second.first;
            Q.pop();

            unreachable = false;

            recurtsp(nextSrc, Nodes, Dummy);
        }

        Nodes.insert(src);

        if (deadEnd)
        {
            if (Q.empty())
            {
                return;
            }
            else
            {
                nextSrc = Q.top().second.first;
                Dummy = Q.top().second.second;
                finalCost = Q.top().first;
                Q.pop();
                while ((Nodes.find(nextSrc) == Nodes.end()))
                {
                    if (Q.empty())
                    {
                        return;
                    }
                    nextSrc = Q.top().second.first;
                    Dummy = Q.top().second.second;
                    finalCost = Q.top().first;
                    Q.pop();
                }
                deadEnd = false;
                path.pop_back();
                recurtsp(nextSrc, Nodes, Dummy);
            }
        }

        while (finalCost > Q.top().first && !Q.empty())
        {
            cout << "Are we reaching here by any chance?" << endl;
            Dummy = Q.top().second.second;
            finalCost = Q.top().first;
            int nextSrc = Q.top().second.first;
            Q.pop();

            recurtsp(nextSrc, Nodes, Dummy);
        }

        /*
         * Compare finalCost with the new Q.top()
         * if finalCost is less: win
         * else: I have no idea lol
         */
    }
}

void tsp(int src, set<int> Nodes, vector<vector<int>> Cost)
{
    origSrc = src;
    finalCost = reductionCost(Cost);
    recurtsp(src, Nodes, Cost);
    cout << "Path: ";
    pathPrint();
    cout << src;
    paragraph;

    cout << "Cost: " << finalCost << endl;
}

int main()
{
    cout << "Enter Number of Nodes and Number of Edges: ";
    cin >> node_no >> edge_no;
    node_no++; // As 0 is not counted as a node
    paragraph;

    set<int> Nodes;
    vector<vector<int>> Cost(node_no, vector<int>(node_no, INF));
    inPath.resize(node_no, false);
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
    paragraph;

    tsp(src, Nodes, Cost);
    paragraph;
}
