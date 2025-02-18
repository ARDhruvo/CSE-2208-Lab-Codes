#include <bits/stdc++.h>
using namespace std;

/*
ABCB
BDCAB

ABCBDAB
BDCABA

*/

#define paragraph cout << endl
// for arrows
#define diagonal 0
#define left -1
#define up 1
#define none 2

vector<vector<int>> c, b; // c = length matrix, b = arrow matrix

void printLCS(string X, int i, int j)
{
    if ((i == 0) || (j == 0)) // Reaching start of table
    {
        return;
    }
    if (b[i][j] == diagonal) // If the arrow is diagonal then there is a common letter
    {
        printLCS(X, i - 1, j - 1); // To ensure it is not reversed
        cout << X[i - 1];          // Printing the common letter
    }
    else if (b[i][j] == up)
    {
        printLCS(X, i - 1, j);
    }
    else
    {
        printLCS(X, i, j - 1);
    }
}

void LCS(string X, string Y)
{
    int m = X.length(), n = Y.length();
    vector<char> ascending;

    c.resize(m + 1, vector<int>(n + 1, 0));
    b.resize(m + 1, vector<int>(n + 1, none));

    // Both vectors are already filled with 0
    /*
    for (int i = 0; i <= m; i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++)
    {
        c[0][j] = 0;
    }
    */

    for (int i = 1; i <= m; i++) // For each letter in X
    {
        for (int j = 1; j <= n; j++) // For each letter in Y
        {
            if (X[i - 1] == Y[j - 1]) // If there is a letter common
            {
                if(ascending.empty())
                {
                    ascending.push_back(X[i-1]);
                }
                else if(ascending.back() <= X[i-1])
                {
                    ascending.push_back(X[i-1]);
                }
                c[i][j] = c[i - 1][j - 1] + 1; // Length = Diagonal Length + 1
                b[i][j] = diagonal;            // Setting arrow to diagonal
            }
            else if (c[i - 1][j] >= c[i][j - 1]) // If up is greater
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = up;
            }
            else // If left is greater
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = left;
            }
        }
    }

    for (char x : ascending)
    {
        cout << x;
    }
    paragraph;
    

    cout << "LCS: ";
    printLCS(X, m, n);
    cout << "\tLength: " << c[m][n] << endl;
}

int main()
{
    string X, Y;
    cout << "Enter String X:" << endl;
    getline(cin, X);
    paragraph;
    cout << "Enter String Y:" << endl;
    getline(cin, Y);
    paragraph;

    LCS(X, Y);
}
