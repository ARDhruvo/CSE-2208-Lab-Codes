#include <bits/stdc++.h>
using namespace std;

/*
Q: Given,
D[2] =
        1    2    3    4    5
1       0    3    8    4    -4
2       INF  0    INF  1    7
3       INF  4    0    5    11
4       2    5    -5   0    -2
5       INF  INF  INF  6    0

and Pi[2] =
        1    2    3    4    5
1       NIL  1    1    2    1
2       NIL  NIL  NIL  2    2
3       NIL  3    NIL  2    2
4       4    1    4    NIL  1
5       NIL  NIL  NIL  5    NI

Using the above data, find D[3] and print all paths




Output matrix
        1    2    3    4    5
1       0    3    8    4    -4
2       INF  0    INF  1    7
3       INF  4    0    5    11
4       2    -1   -5   0    -2
5       INF  INF  INF  6    0
 */

#define paragraph cout << endl
#define INF 255 // Using 255 as infinity for the cost matrix
#define NIL -1   // Using -1 as nil for the predecessor matrix

int node_no = 6;       // Hard Coded to a 5 x 5 matrix
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

void floydWarshall(vector<vector<int>> W, vector<vector<int>> Pre)
{
    int n = 5;                                           // code doesn't work when n isn't 5
    // Don't ask me why, idk why
    vector<vector<vector<int>>> D(n, vector<vector<int>>(n));  // D matrix for the cost updates
    vector<vector<vector<int>>> Pi(n, vector<vector<int>>(n)); // Pi matrix for the predecessor updates
    D[2] = W;                                                  // Given matrix was D2
    Pi[2] = Pre;                                               // Given matrix was Pi2
    for (int k = 3; k < n; k++) // Running to find D3
    {
        // Setting the k-th iteration as its past one so even if no changes in this iteration
        // the next one can keep using the previous one
        D[k] = D[k - 1];
        Pi[k] = Pi[k - 1];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (D[k][i][j] > (D[k][i][k] + D[k][k][j]))
                {
                    // Updates the cost if the journey using k nodes makes it cheaper
                    D[k][i][j] = (D[k][i][k] + D[k][k][j]); // Updates to the cost of using k nodes
                    Pi[k][i][j] = Pi[k][k][j];                  // Updates to the node of the new cost node's predecessor
                }
            }
        }
    }
    paragraph;

    // Required output

    cout << "Floyd Completed ";
    adjMatrix(D[3]);

    for (int i = 1; i < node_no; i++) // Prints ALL path
    {
        cout << "From " << i << " to " << endl;
        for (int j = 1; j < node_no; j++)
        {
            cout << j << ": ";
            printPath(Pi[n - 1], i, j);
            if(D[n - 1][i][j]!= INF)
            {
                cout << " Cost: " << D[n - 1][i][j] << endl;
            }

        }
        paragraph;
    }

    // For updating the matrices globally if they need to be accessed from elsewhere
    Dn = D[3];
    Pin = Pi[3];
}

int main()
{
    vector<vector<int>> W(node_no, vector<int>(node_no, INF));   // Cost Matrix
    vector<vector<int>> Pre(node_no, vector<int>(node_no, NIL)); // Predecessor Matrix

    // Given hardcoded state
    W =
    {
        {0, 0, 0, 0, 0, 0}, // W[0] will be here but it will not be accessible
        {0, 0, 3, 8, 4, -4},
        {0, INF, 0, INF, 1, 7},
        {0, INF, 4, 0, 5, 11},
        {0, 2, 5, -5, 0, -2},
        {0, INF, INF, INF, 6, 0}
    };

    Pre =
    {
        {NIL, NIL, NIL, NIL, NIL, NIL}, // Pre[0] will be here but it will not be accessible
        {NIL, NIL, 1, 1, 2, 1},
        {NIL, NIL, NIL, NIL, 2, 2},
        {NIL, NIL, 3, NIL, 2, 2},
        {NIL, 4, 1, 4, NIL, 1},
        {NIL, NIL, NIL, NIL, 5, NIL}
    };

    // Printing the input graph
    adjMatrix(W);
    preMatrix(Pre);
    paragraph;

    floydWarshall(W, Pre);
}
