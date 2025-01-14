#include <bits/stdc++.h>
using namespace std;


int main()
{
    map<int, string> m;
    m[1] = "abc";
    m[3] = "efg";
    m[4] = "aaa";
    m.insert({2, "bbb"});

    for (auto it = m.begin(); it != m.end(); it++)
    {
        cout << it -> first << ": " << it -> second << endl;
    }

    auto it = m.find(3);
    if(it == m.end())
    {
        cout << "Value not found" << endl;
    }
    else
    {
        cout << it-> second << endl;
    }
    if(it != m.end())
    {
        m.erase(3);
    }
    else
    {
        cout << "Value cannot be erased" << endl;
    }

}
