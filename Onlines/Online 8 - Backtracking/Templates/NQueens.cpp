#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

vector<int> x;   // Solution Set
int solnNum = 0; // Tracking number of solutions

void printSolution()
{
    solnNum++;
    cout << "Solution " << solnNum << " :\t" << "[ ";
    for (int i : x)
    {
        if (i == 0)
        {
            continue;
        }
        cout << i << " ";
    }

    cout << "]" << endl;
}

bool place(int k, int i)
{
    for (int j = 1; j <= k - 1; j++)
    {
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k))) // For checking same column || diagonal
        {
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n)
{
    for (int i = 1; i <= n; i++) // Iterating tiles
    {
        if (place(k, i)) // Checking if queen can be placed
        {
            x[k] = i;   // Putting k-th queen on i-th tile
            if (k == n) // Checking if last queen
            {
                printSolution();
            }
            else
            {
                NQueens(k + 1, n); // For next queen placement
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter number of Queens: ";
    cin >> n;
    paragraph;

    x.resize(n + 1, 0);

    NQueens(1, n);

    if (solnNum < 1) // If there aren't any solutions acquired
    {
        cout << "No possible Solutions" << endl;
    }
}
