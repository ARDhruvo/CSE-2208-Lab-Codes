#include <bits/stdc++.h>
using namespace std;

// Online: Use Quick Sort to find the median in odd number of data
// Next step: Find the even one as well

vector<int> A;
bool found = false;
int med_index;

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
    if ((lo < hi) && (found == false))
    {
        int p = part(lo, hi);
        if(p == med_index)
        {
            cout << "Median: " << A[p] << endl;
            found = true;
            return;
        }
        else if(p < med_index)
        {
            quickSort(p + 1, hi);
        }
        else
        {
            quickSort(lo, p - 1);
        }


    }
}

int main()
{
    int x;
    for (int i = 0; i < 9; i++)
    {
        cin >> x;
        A.push_back(x);
    }
    med_index = (A.size()/2);
    quickSort(0, A.size()-1);
}
