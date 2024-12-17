#include<bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define WHITE -1
#define GRAY 0
#define BLACK 1

/*Online: 
 * Make a graph
 * Run DFS from wherever on the graph
 * Make a data structure which will take the end nodes in a path
 * Print it later
 */ 


/* Use for input:
6
4
1 2
2 3
2 4
5 6
 */



vector<int>Node_Vec[100];
vector<int> path;
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
    path.push_back(u);
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
    DFS(1); // Assuming source = 1
    DFS(5); // Assuming source = 5
    paragraph;
    for(int num: path)
    {
        cout << num << " ";
    }
    paragraph;
}

