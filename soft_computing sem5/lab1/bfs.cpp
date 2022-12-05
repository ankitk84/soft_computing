#include <bits/stdc++.h>

using namespace std;

void bfs(int src, vector<int> adj[], vector<int> &vis)
{
    queue<int> q;

    q.push(src);
    vis[src] = 1;

    while (!q.empty())
    {
        int src = q.front();
        q.pop();
        cout << src << " ";
        for (int dest : adj[src])
        {
            if (vis[dest])
                continue;
            vis[dest] = 1;
            q.push(dest);
        }
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

    cout << "Enter the source node for bfs : ";
    int src;
    cin >> src;

    cout << "BFS traversal of the given graph : ";

    bfs(src, adj, vis);

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            bfs(i, adj, vis);
    }

    return 0;
}