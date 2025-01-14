#include <bits/stdc++.h>
using namespace std;

struct Node
{
    vector<vector<int>> array;
    int cost;
    string path;

    Node(vector<vector<int>> arr, int c, string p)
    {
        array = arr;
        cost = c;
        path = p;
    }
};

struct Compare
{
    bool operator()(Node a, Node b)
    {
        return a.cost > b.cost;
    }
};

void displayNode(priority_queue<Node, vector<Node>, Compare> pq)
{
    while (!pq.empty())
    {
        Node a = pq.top();
        cout << a.cost << " " << a.path << endl;
        pq.pop();
    }
}

int reduction(vector<vector<int>> array, int size)
{
    int total_cost = 0;

    for(int j = 0; j < size; j++)
    {
        int min_val = array[j][0];
        for(int i = 1; i < size; i++)
        {
            min_val = min(min_val, array[j][i]);
        }
        total_cost += min_val;
        for(int i=0; i < size; i++)
        {
            array[j][i] -= min_val;
        }
    }

    for(int j = 0; j < size; j++)
    {
        int min_val = array[0][j];
        for(int i = 1; i < size; i++)
        {
            min_val = min(min_val, array[i][j]);
        }
        total_cost += min_val;
        for(int i=0; i < size; i++)
        {
            array[i][j] -= min_val;
        }
    }

    return total_cost;
}

int main()
{
    Node data1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 100, "Path 1");
    Node data2({{5, 6, 10}, {7, 8, 11}, {10, 12, 15}}, 50, "Path 2");
    Node data3({{9, 10, 12}, {11, 12, 15}, {12, 15, 20}}, 70, "Path 3");
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(data1);
    pq.push(data2);
    pq.push(data3);
    displayNode(pq);

    priority_queue<Node, vector<Node>, Compare> pq1;
    data1.cost = reduction(data1.array, data1.array[0].size());
    data2.cost = reduction(data2.array, data2.array[0].size());
    data3.cost = reduction(data3.array, data3.array[0].size());
    pq1.push(data1);
    pq1.push(data2);
    pq1.push(data3);
    cout << "::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    displayNode(pq1);
}
