#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl
#define INF INT_MAX

vector<int> p;         // Dimension matrix where A[i] has the dimension of p[i-1] x p[i]
vector<vector<int>> m; // Minimum scalar multiplication matrix
vector<vector<int>> s; // Split matrix

void printTables()
{
    cout << "Cost Table:" << endl;
    for (int i = 1; i < p.size(); i++)
    {
        cout << "\t" << i;
    }
    paragraph;

    for (int i = 1; i < p.size(); i++)
    {
        cout << i;
        for (int j = 1; j < p.size(); j++)
        {
            if (j < i) // Lower triangle is not necessary
            {
                cout << "\t";
            }
            else
            {
                cout << "\t" << m[i][j];
            }
        }
        paragraph;
    }

    paragraph;

    cout << "Split Table:" << endl;
    for (int i = 1; i < p.size(); i++)
    {
        cout << "\t" << i;
    }
    paragraph;
    for (int i = 1; i < p.size(); i++)
    {
        cout << i;
        for (int j = 1; j < p.size(); j++)
        {
            if (j <= i) // Lower triangle and leading diagonal are not necessary
            {
                cout << "\t";
            }
            else
            {
                cout << "\t" << s[i][j];
            }
        }
        paragraph;
    }
}

void printOptimalParens(vector<vector<int>> s, int i, int j)
{
    if (i == j) // Splitting the matrix with itself
    {
        cout << "A" << i << " ";
    }
    else
    {
        cout << "( ";
        printOptimalParens(s, i, s[i][j]);     // To split from i to j
        printOptimalParens(s, s[i][j] + 1, j); // To split from j to end
        cout << ")";
    }
}

void mcm()
{
    int n = p.size(); // n = number of matrices
    for (int i = 1; i < n; i++)
    {
        m[i][i] = 0; // Setting Diagonal to 0
    }

    for (int l = 2; l < n; l++) // Taking l matrices at a time
    {
        for (int i = 1; i < n - l + 1; i++) // Starting from i-th matrix
        {
            int j = i + l - 1;          // Taking up to j-th matrix; j-th matrix is l matrix away from i-th matrix
            m[i][j] = INF;              // Setting the cost of m[i, j] to INF to calculate minimum cost later
            for (int k = i; k < j; k++) // Splitting up to k-th matrix
            {
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]); // Total Cost = min((Cost of i to k) + (Cost of k+1 to j) + (p[i-1] * p[k] * p[j]))
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    printTables();
    paragraph;
    printOptimalParens(s, 1, n - 1);
    paragraph;
    cout << "Cost: " << m[1][n - 1] << endl;
}

int main()
{
    int n;
    cout << "Enter Chain Length: ";
    cin >> n;
    p.resize(n);
    m.resize(n, vector<int>(n));
    s.resize(n, vector<int>(n));
    paragraph;

    cout << "Enter Corresponding dimensions ( p0 -> p" << n - 1 << " ):" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    paragraph;

    // For printing the dimension matrix
    cout << "p = [ ";
    for (int i : p)
    {
        cout << i << " ";
    }
    cout << "]" << endl;
    paragraph;

    mcm();
}
