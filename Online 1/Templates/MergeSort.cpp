#include <bits/stdc++.h>
using namespace std;

void printing(vector<int> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << endl;
}

void Merge(vector<int> &A, int low, int mid, int high)
{
    int m = mid - low + 1; // First half of this half
    int n = high - mid; // Other half
    int Left[m + 1], Right[n + 1]; // Two Arrays to store the halves of datas
    int i = 0, j = 0; // For loop and track
    for (i; i < m; i++)
    {
        Left[i] = A[low + i]; // Left stores the first half
    }
    for (j = 0; j < n; j++)
    {
        Right[j] = A[mid + 1 + j]; // Right stores the second half
    }
    Left[m] = INT_MAX; // Storing the highest possible value for comparison later
    Right[n] = INT_MAX;
    i = 0; // Resetting the (loop and track) variables
    j = 0;

    /* The Magic of Conquering */
    for (int k = low; k <= high; k++) 
    // k starts from the currently lowest index since it will not always be 0
    // it runs until the currently highest index to ensure all data makes it
    {
        // Checks which data is smallest and inserts it in the original vector
        if (Left[i] <= Right[j]) 
        {
            A[k] = Left[i];
            i++;
        }
        else
        {
            A[k] = Right[j];
            j++;
        }
    }
}

void MergeSort(vector<int> &A, int low, int high)
{
    if (low < high)
    {
        int mid = (high + low) / 2; // Finding the middle point
        MergeSort(A, low, mid); // Dividing the first half
        MergeSort(A, mid + 1, high); // Dividing the second half
        Merge(A, low, mid, high); // Conquering the currently active half
    }
}

int main()
{
    vector<int> A, Asorted;
    for (int i = 0; i < 10; i++)
    {
        int x;
        cin >> x;
        A.push_back(x);
    }
    cout << endl;
    printing(A);
    cout << endl;
    MergeSort(A, 0, A.size() - 1);
    cout << endl;
    printing(A);
}
