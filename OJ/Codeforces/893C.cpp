#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 100000 + 100
#define MAX_E 100000 + 100

using namespace std;
typedef long long ll;

vector<int> G[MAX_V];
int V, E;
ll c[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
ll dfs(int v){
    used[v] = true;
    ll res = c[v];
    for(int i = 0; i < G[v].size(); i++){
        if(!used[G[v][i]]){
            res = min(res, dfs(G[v][i]));
        }
    }
    return res;
}
ll solve(){
    memset(used, false, sizeof(used));
    ll res = 0;
    for(int v = 0; v < V; v++){
        if(!used[v]) res += dfs(v);
    }
    return res;
}
int main(){
    cin >> V >> E;
    for(int i = 0; i < V; i++){
        scanf("%d", c + i);
    }
    for(int i = 0; i < E; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        add_edge(a - 1, b - 1);
    }
    cout << solve() << endl;
    return 0;
}