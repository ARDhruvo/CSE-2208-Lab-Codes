#include<bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

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
int level[12]; // depends on the size of input

void BFS(int source)
{
    queue <int> Q;
    Q.push(source);
    level[source] = 0;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int j = 0; j < Node_Vec[u].size(); j++) // Same loop as printing
        {
            int v = Node_Vec[u][j];
            if(level[v] == -1)
            {
                level[v] = level[u] + 1;
                Q.push(v);
            }
        }
    }
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
        level[i] = -1;
    }
    paragraph;
    cout << "Enter source: ";
    cin >> src;
    cout << "Enter destination: ";
    cin >> dst;
    BFS(src); // Assuming source = 1
    paragraph;
    cout << "Distance = " << level[dst] << endl; // Distance from source to 10
}

