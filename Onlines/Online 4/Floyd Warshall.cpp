#include <bits/stdc++.h>
using namespace std;

/*
Input from slide
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
 */

#define paragraph cout << endl
#define INF 255 // Using 255 as infinity for the cost matrix
#define NIL 0   // Using 0 as nil for the predecessor matrix

int node_no, edge_no;        // Number of edges and nodes
vector<vector<int>> Dn, Pin; // For saving the final results globally to be accessed from anywhere

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
            if (W[i][j] != INF) // Checks if there is connection with j-th node
            {
                cout << W[i][j];
                if (W[i][j] >= 0) // Checks negative for spacing reasons
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

void printPath(vector<vector<int>> Pi, int i, int j) // Recursive print path from i to j
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
        printPath(Pi, i, Pi[i][j]); // Recursively reaches the source and then goes back to the immediate after node until reaching the destination
        cout << " -> " << j;
    }
}

void floydWarshall(vector<vector<int>> W, vector<vector<int>> Pre) //,int src, int dest)
{
    // cout << "Floyd Started " << endl;
    int n = node_no;                                           // n represents the number of iterations it will take to reach the final matrix
    vector<vector<vector<int>>> D(n, vector<vector<int>>(n));  // D matrix for the cost updates
    vector<vector<vector<int>>> Pi(n, vector<vector<int>>(n)); // Pi matrix for the predecessor updates
    D[0] = W;                                                  // Setting D0 as the first matrix; 0 because k starts from 1 and needs a previous state to compare with
    Pi[0] = Pre;                                               // Setting Pi0 as the first matrix; 0 because k starts from 1 and needs a previous state to compare with
    for (int k = 1; k < n; k++)
    {
        // Setting the k-th iteration as its past one so even if no changes in this iteration
        // the next one can keep using the previous one
        D[k] = D[k - 1];
        Pi[k] = Pi[k - 1];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                // D[k][i][j] = min(D[k-1][i][j], (D[k-1][i][k] + D[k-1][k][j])); // For only Cost Adjacency Matrix
                if (D[k - 1][i][j] > (D[k - 1][i][k] + D[k - 1][k][j]))
                {
                    // Updates the cost if the journey using k nodes makes it cheaper
                    D[k][i][j] = (D[k - 1][i][k] + D[k - 1][k][j]); // Updates to the cost of using k nodes
                    Pi[k][i][j] = Pi[k - 1][k][j];                  // Updates to the node of the new cost node's predecessor
                }
            }
        }
    }
    paragraph;

    // For debugging purposes
    /*
    cout << "Floyd Completed ";
    adjMatrix(D[n-1]);
    cout << "Floyd Completed ";
    preMatrix(Pi[n-1]);
     */

    for (int i = 1; i < n; i++) // Prints ALL path
    {
        cout << "From " << i << " to " << endl;
        for (int j = 1; j < n; j++)
        {
            cout << j << ": ";
            printPath(Pi[n - 1], i, j);
            cout << " Cost: " << D[n - 1][i][j] << endl;
        }
        paragraph;
    }

    // For updating the matrices globally if they need to be accessed from elsewhere
    Dn = D[n - 1];
    Pin = Pi[n - 1];

    // For single path only
    /*
    cout << "From " << src << " to " << dest << ": " << endl;
    printPath(Pi[n-1], src, dest);
    cout << " Cost: " << D[n-1][src][dest] << endl;
    paragraph;
    */
}

int main()
{
    cout << "Enter Number of Nodes and Edges: ";
    cin >> node_no >> edge_no;
    paragraph;
    node_no++; // This is because we don't count 0 as node

    vector<vector<int>> W(node_no, vector<int>(node_no));   // Cost Matrix
    vector<vector<int>> Pre(node_no, vector<int>(node_no)); // Predecessor Matrix

    for (int i = 1; i < node_no; i++) // Initialized both matrices
    {
        for (int j = 1; j < node_no; j++)
        {
            W[i][j] = INF;   // Sets all cost at the start to infinity
            Pre[i][j] = NIL; // Sets all predecessor at NIL
            // This basically makes taking the inputs much smoother as they
            // get replaced later anyways
        }
        W[i][i] = 0; // Sets diagonal to 0 as the cost for reaching a node from that node will always be 0 (unless specified)
    }

    cout << "Enter Connections: " << endl;
    for (int i = 1; i <= edge_no; i++)
    {
        int nodeA, nodeB, cost;
        cin >> nodeA >> nodeB >> cost;
        W[nodeA][nodeB] = cost;    // Sets the [i][j]-th element of the matrix to be its cost
        Pre[nodeA][nodeB] = nodeA; // Sets the [i] as [j]'s predecessor
    }
    paragraph;

    // Printing the input graph
    adjMatrix(W);
    preMatrix(Pre);
    paragraph;

    // For finding out specific path and cost between any two nodes
    /*
    int src, dest;
    cout << "Enter source and destination: ";
    cin >> src >> dest;
    */
    floydWarshall(W, Pre); //, src, dest);

    // For debugging purposes
    /*
    adjMatrix(Dn);
    preMatrix(Pin);
    */
}
