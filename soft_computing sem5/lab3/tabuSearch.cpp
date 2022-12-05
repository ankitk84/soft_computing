#include <bits/stdc++.h>
#define ll long long
using namespace std;

int nodes, edges;
const int MAX = 1E4;
int id[MAX];
set<pair<ll, pair<int, int>>> mst;
set<pair<ll, pair<int, int>>> graph;
pair<ll, pair<int, int>> p[MAX];

// DSU implementation

void init()
{
    for (int i = 1; i <= nodes; i++)
        id[i] = i;
}

int root(int i)
{
    while (id[i] != i)
    {
        i = id[i];
    }
    return i;
}

void union1(int a, int b)
{
    int p1 = root(a);
    int p2 = root(b);
    id[p1] = id[p2];
}

ll kruskal()
{
    ll mincost = 0, cost;
    int x, y;
    for (int i = 0; i < edges; i++)
    {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        if (root(x) != root(y))
        {
            mincost += cost;
            mst.insert(p[i]);
            union1(x, y);
        }
    }
    return mincost;
}

bool ismst(set<pair<ll, pair<int, int>>> mst)
{
    init();
    int x, y;
    for (auto p : mst)
    {
        x = p.second.first;
        y = p.second.second;
        if (root(x) == root(y))
            return false;
        union1(x, y);
    }
    return true;
}

int cost(set<pair<ll, pair<int, int>>> mst)
{
    int ans = 0;
    for (auto i : mst)
    {
        ans += i.first;
    }
    if (mst.find({15, {1, 4}}) != mst.end() && mst.find({40, {4, 5}}) == mst.end())
        ans += 100;
    int ctr = 0;
    if (mst.find({15, {1, 4}}) != mst.end())
        ctr++;
    if (mst.find({25, {3, 4}}) != mst.end())
        ctr++;
    if (mst.find({20, {1, 2}}) != mst.end())
        ctr++;
    if (ctr == 2)
        ans += 100;
    if (ctr == 3)
        ans += 200;

    return ans;
}

set<pair<ll, pair<int, int>>> tabuSearch(set<pair<ll, pair<int, int>>> mst)
{
    set<pair<ll, pair<int, int>>> cmst = mst;
    set<pair<ll, pair<int, int>>> rem;
    for (auto i : graph)
    {
        if (mst.find(i) == mst.end())
            rem.insert(i);
    }
    set<pair<ll, pair<int, int>>> aset;
    int ans = INT_MAX;

    for (auto i : rem)
    {
        cmst.insert(i);
        for (auto j : mst)
        {
            cmst.erase(j);
            if (ismst(cmst))
            {
                if (cost(cmst) < ans)
                {
                    ans = cost(cmst);
                    aset = cmst;
                }
            }
            cmst.insert(j);
        }
        cmst.erase(i);
    }

    return aset;
}

void util(set<pair<ll, pair<int, int>>> mst, int itr)
{
    set<pair<ll, pair<int, int>>> ans = mst;
    for (int i = 1; i <= itr; i++)
    {
        ans = tabuSearch(ans);
    }
    int ok = 0;
    for (auto i : ans)
        ok += i.first;
    cout << ok << endl;
}

int main()
{
    int x, y;
    ll w;
    cin >> nodes >> edges;
    init();
    for (int i = 0; i < edges; i++)
    {
        cin >> x >> y >> w;
        p[i] = {w, {x, y}};
        graph.insert({w, {x, y}});
    }
    sort(p, p + edges);
    ll mincost;
    mincost = kruskal();
    // if(ismst(mst))
    // cout<<"yes"<<endl;
    //    else cout<<"no"<<endl;
    for (int i = 1; i <= 25; i++)
        util(mst, i);
    // cout<<graph.size()<<endl;

    // cout<<mincost<<endl;
}