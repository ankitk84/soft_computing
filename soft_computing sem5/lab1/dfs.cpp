#include <bits/stdc++.h>

using namespace std;

void dfs(int src, vector<int> adj[], vector<int> &vis)
{
    cout << src << " ";
    vis[src] = 1;
    for (int dest : adj[src])
    {
        if (vis[dest])
            continue;
        dfs(dest, adj, vis);
    }
}

int main()
{

    int n;
    cout << "Enter the number of nodes in the graph : ";
    cin >> n;

    vector<int> adj[n];

    int m;
    cout << "Enter the number of edges : ";
    cin >> m;

    cout << "Enter " << m << " edges : " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n, 0);

    cout << "Enter the source node for dfs : ";
    int src;
    cin >> src;

    cout << "DFS traversal of the given graph : ";

    dfs(src, adj, vis);
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(i, adj, vis);
    }

    return 0;
}