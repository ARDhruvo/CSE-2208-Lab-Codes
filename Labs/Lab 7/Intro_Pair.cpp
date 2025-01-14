#include <bits/stdc++.h>
using namespace std;


int main()
{
    vector<vector<int>> matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    pair<int, int> test = {4,4};
    pair <vector<vector<int>>, int> my_pair = make_pair(matrix, 1000); // Also works with (,)
    cout << "Second Element: " << my_pair.second << endl;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << my_pair.first[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "New Pair" << endl;
    pair<pair <vector<vector<int>>, int>, string> myNewPair = make_pair(my_pair, "Hello");
    cout << "Second Element: " << myNewPair.second << endl;
    cout << "First Element (Second Element):" << myNewPair.first.second << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << myNewPair.first.first[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
