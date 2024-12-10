#include <bits/stdc++.h>
using namespace std;

void BinSearch(vector<int> A, int key)
{
    int low = 0, high = A.size() - 1;
    while(low <= high)
    {
        int mid = (high + low)/2;
        if(A[mid] == key)
        {
            cout << "Found" << endl;
            return;
        }
        else if(A[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << "Not Found" << endl;
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
    BinSearch(A, y);
}