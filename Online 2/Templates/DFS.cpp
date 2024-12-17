#include<bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define WHITE -1
#define GRAY 0
#define BLACK 1

/* Use for input:
1 2
1 4
1 3
2 6
4 7
3 8
3 7
6 10
9 10
9 7
7 8
8 5
10 5
 */

vector<int>Node_Vec[100];
int color[12]; // depends on the size of input

void DFS(int u)
{
    color[u] = GRAY;
    for(int i = 0; i < Node_Vec[u].size(); i++)
    {
        int v = Node_Vec[u][i];
        if(color[v] == WHITE)
        {
            DFS(v);
        }
    }
    color[u] = BLACK;
}

int main()
{
    int node_no, edge_no, src, dst;
    cout << "Enter the number of nodes: ";
    cin >> node_no;
    cout <<"Enter the number of edges: ";
    cin >> edge_no;
    cout << "Enter connections:" << endl;
    for(int i = 1; i <= edge_no; i++)
    {
        int nodeA, nodeB;
        scanf("%d %d", &nodeA, &nodeB);
        Node_Vec[nodeA].push_back(nodeB);
        Node_Vec[nodeB].push_back(nodeA); // for undirected graph
    }
    paragraph;


// Print Node Adjacency List by traversing the list
    cout << "Adjacency List:" << endl;
    for(int i = 1; i <= node_no; i++)
    {
        cout << i << " -> ";
        for(int j = 0; j < Node_Vec[i].size(); j++)
        {
            cout << Node_Vec[i][j] << " ";
        }
        paragraph;
    }

    for(int i = 0; i <= node_no; i++)
    {
        color[i] = WHITE;
    }
    paragraph;
    cout << "Enter source: ";
    cin >> src;
    cout << "Enter destination: ";
    cin >> dst;
    DFS(src); // Assuming source = 1
    paragraph;
    cout << "Distance = " << color[dst] << endl; // Distance from source to 10
}

