#include <bits/stdc++.h>
using namespace std;

void printing(vector<int> V)
{
    for(int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << endl;
}

vector<int> InsertionSort(vector<int> A)
{
    for(int j = 1; j < A.size(); j++) // Runs a loop from 2nd to the last index of the data structure
    {
        int key = A[j]; // Storing the data in the current index in key for comparison
        int i = j - 1; // Taking i as an index to compare with all the previous "unsorted" index
        
        /* This is where the magic happens */
        while((i >= 0) && (A[i] > key)) 
        // The loop runs as long as the key is smaller than its previous indices and i isn't the first index
        {
            A[i+1] = A[i]; // This swaps the [smaller] number on the later indices with the [greater] number of the previous indices
            i--;
        }
        A[i+1] = key; // Inserts key in its position; [0] if key is smallest OR sorted position
    }
    return A;
}

int main()
{
    vector<int> A, Asorted;
    for(int i = 0; i <10; i++)
    {
        int x;
        cin >> x;
        A.push_back(x);
    }
    cout << endl;
    printing(A);
    cout << endl;
    Asorted = InsertionSort(A);
    cout << endl;
    printing(Asorted);
}
