#include <bits/stdc++.h>
using namespace std;

/*
5 4
2 3
3 4
4 5
5 6
*/

#define paragraph cout << endl

vector<pair<int, int>> b; // b = {weight, benefit}

void printItems() // For indexing items to understand later
{
    cout << "Input items:\nNo.\tWeight\tBenefit" << endl;
    for (int i = 1; i < b.size(); i++)
    {
        cout << i << ":\t" << b[i].first << "\t" << b[i].second << endl;
    }
}

void knapsack(int W, int n)
{
    vector<vector<int>> V(W + 1, vector<int>(n + 1, 0)); // Matrix with the highest benefit

    // V is already filled with 0
    /*
    for (int w = 0; w <= W; W++)
    {
        V[0][w] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        V[i][0] = 0;
    }
    */

    for (int i = 1; i <= n; i++) // For each item
    {
        for (int w = 1; w <= W; w++) // For capacity of knapsack
        {
            if (b[i].first <= w) // If weight of i-th item < current capacity of knapsack
            {
                if ((b[i].second + V[i - 1][w - b[i].first]) > V[i - 1][w]) // b[i] + V[i - 1, w - w[i]] > V[i - 1, w]
                {
                    V[i][w] = (b[i].second + V[i - 1][w - b[i].first]); // Current benefit = benefit of i-th item + benefit of items of remaining capacity
                }
                else
                {
                    V[i][w] = V[i - 1][w]; // i-th item is not more benefecial
                }
            }
            else
            {
                V[i][w] = V[i - 1][w]; // i-th item is not within knapsack capacity
            }
        }
    }

    int i = n, k = W;
    set<int> items; // Indexes of items to be taken in knapsack
    while (i != 0)
    {
        if (V[i][k] != V[i - 1][k]) // If benefit of taking i-th item is different from benefit of upto previous item
        {
            // This is because benefit changes if a new item is taken in the knapsack
            items.insert(i);
            k -= b[i].first;
            i--;
        }
        else
        {
            i--;
        }
    }

    cout << "The optimal Knapsack contains:\n{ ";
    for (int i : items)
    {
        cout << i << " ";
    }
    cout << "} : " << V[n][W] << endl;
}

int main()
{
    int W, n; // W = Capacity of Knapsack, n = Number of items
    cout << "Enter Capacity of Knapsack and number of items: ";
    cin >> W >> n;
    b.resize(n + 1);
    paragraph;

    cout << "Enter Item Weight and its Benefit:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i].first >> b[i].second;
    }
    paragraph;

    printItems(); // For giving indexes to items
    paragraph;

    knapsack(W, n);
}
