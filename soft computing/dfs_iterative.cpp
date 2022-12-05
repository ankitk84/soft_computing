#include<bits/stdc++.h>

using namespace std;

int main(){

    int v;cin>>v;
    vector<int> adj[v];

    int e;cin>>e;
    for(int i=0;i<e;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    stack<int> st;
    int src;
	cin>>src;
    vector<int> vis(v,0);
    st.push(src);
    vis[src]=1;
    while(!st.empty()){
        int s=st.top();st.pop();
        cout<<s<<" ";
        for(int i=0;i<adj[s].size();i++){
        	int dest=adj[s][i];
            if(vis[dest]) continue;
            vis[dest]=1;
            st.push(dest);
        }
    }
    return 0;
}
