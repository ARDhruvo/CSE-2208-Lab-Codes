#include <bits/stdc++.h>
using namespace std;

void BinSearch(vector<int> A, int key, int low, int high)
{
    if(low <= high)
    {
        int mid = (low + high)/2;
        if(A[mid] == key)
        {
            cout << "Found" << endl;
        }
        else if(A[mid] > key)
        {
            BinSearch(A, key, low, mid-1);
        }
        else
        {
            BinSearch(A, key, mid+1, high);
        }
    }
    else
    {
        cout << "Not Found" << endl;
    }
}

int main()
{
    vector<int> A;
    for(int i = 0; i <10; i++)
    {
        int x;
        cin >> x;
        A.push_back(x);
    }
    cout << endl;
    int y;
    cin >> y;
    BinSearch(A, y, 0, A.size()-1);
}