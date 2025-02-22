#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

vector<int> x, w;   // x = Solution Set, w = Value Set
int solnNum = 1, m; // Tracking number of solutions, m = Sum to acquire

void printData()
{
    cout << "Sorted Input:\t";
    for (int i = 1; i < w.size(); i++)
    {
        cout << w[i] << " ";
    }
    paragraph;
}

void printSolution()
{
    cout << "Solution " << solnNum << " :\t" << "[ ";
    for (int i = 1; i < w.size(); i++)
    {
        cout << x[i] << " ";
    }

    cout << "]" << endl;
    solnNum++;
}

bool possible(int r)
{
    if (w[1] > m) // If lowest term > sum, then the actual sum will never be acquired
    {
        return false;
    }
    if (r < m) // If sum of values < sum, then actual sum will never be acquired
    {
        return false;
    }
    return true;
}

void SumOfSubs(int s, int k, int r) // s = current sum, k = current index of data, r = current remaining sum
{
    x[k] = 1; // Assuming k-th value is taken

    if (s + w[k] == m) // If current sum + current evaluated value = sum
    {
        printSolution();
    }
    else if (s + w[k] + w[k + 1] < m) // If current sum + current evaluated value + next value < sum
    {
        SumOfSubs(s + w[k], k + 1, r - w[k]); // then the current evaluated value could be taken
    }

    if ((s + r - w[k] >= m) && (s + w[k + 1] <= m)) // If current evaluated value can't be taken
    {
        x[k] = 0; // Removing k-th value from selection
        SumOfSubs(s, k + 1, r - w[k]);
    }
}

int main()
{
    int n;
    cout << "Enter number of elements in set: ";
    cin >> n;
    paragraph;

    int r = 0;
    x.resize(n + 1, 0);
    w.resize(n + 1);
    cout << "Enter values:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        r += w[i];
    }
    stable_sort(w.begin(), w.end());
    paragraph;

    cout << "Enter sum: ";
    cin >> m;
    paragraph;

    printData();
    paragraph;

    if (possible(r))
    {
        SumOfSubs(0, 1, r);
    }
    else
    {
        cout << "No possible solutions" << endl;
    }
}
