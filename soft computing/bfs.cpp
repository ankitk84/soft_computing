#include <bits/stdc++.h>
using namespace std;
    int bfsOfGraph(int V, vector<int>adj[],int src) {
     
      vector < int > vis(V, 0);
      queue < int > q;
      q.push(src);
      vis[src] = 1;
      while (!q.empty()) {
        int node = q.front();
        cout<<node<<" ";
		q.pop();
        for(int i=0;i< adj[node].size();i++) {
        	int it=adj[node][i];
          if (!vis[it]) {
        	q.push(it);
            vis[it] = 1;
            //q.push(it);
          }
        }
      }
      return 0;
    }

int main() {
	int v,e;
	cin>>v>>e;
  vector < int > adj[v];
	for(int i=0;i<e;i++){
    	int u,v;
    	cin>>u>>v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
	}
  
	int src;cin>>src;
  bfsOfGraph(v, adj,src);
 

  return 0;
}
