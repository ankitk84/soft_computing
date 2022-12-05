#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> &vis, vector<int> adj[]) {
		cout<<node<<" ";
        vis[node] = 1; 
        for(int i=0;i< adj[node].size();i++) {
        	int it=adj[node][i];
            if(!vis[it]) {
                dfs(it, vis, adj); 
            }
        }
    }
void dfsOfGraph(int V, vector<int> adj[]){
	    
	    vector<int> vis(V+1, 0); 
      for(int i = 1;i<=V;i++) {
        if(!vis[i]) dfs(i, vis, adj); 
      }
	    return 0; 
	}
int main()
{
	int v,e;
	cin>>v>>e;
	vector<int> adj[v];
    for(int i=0;i<e;i++){
    	int u,v;
    	cin>>u>>v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
	}
    dfsOfGraph(v, adj);
    return 0;
}
