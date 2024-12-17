#include <bits/stdc++.h>
using namespace std;

void LinSearch(vector<int> A, int key)
{
    for(int i = 0; i < A.size(); i++)
    {
        if(A[i] == key)
        {
            cout << "Found" << endl;
            return;
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
    LinSearch(A, y);
}