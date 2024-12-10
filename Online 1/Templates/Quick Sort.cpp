#include <bits/stdc++.h>
using namespace std;

vector<int> A;

void printVect(vector<int> A, int s)
{
    for (int i = 0; i < s; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

int part(int lo, int hi)
{
    int pivot = A[lo];
    int i = lo;
    int j = hi;
    while (i < j)
    {
        while (A[i] <= pivot)
        {
            i++;
        }
        while (A[j] > pivot)
        {
            j--;
        }
        if (i < j)
        {
            swap(A[i], A[j]);
        }
    }
    swap(A[lo], A[j]);
    return j;
}

void quickSort(int lo, int hi)
{
    if (lo < hi)
    {
        int p = part(lo, hi);
        quickSort(lo, p - 1);
        quickSort(p + 1, hi);
    }
}

int main()
{
    int x;
    for (int i = 0; i < 10; i++)
    {
        cin >> x;
        A.push_back(x);
    }
    quickSort(0, 9);
    printVect(A, 10);
}
