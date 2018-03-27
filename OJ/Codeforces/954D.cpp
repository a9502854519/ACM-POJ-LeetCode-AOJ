#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAX_N 1000 + 10
#define INF 1E9

using namespace std;

vector<int> G[MAX_N];
bool adj[MAX_N][MAX_N];
int ds[MAX_N], dt[MAX_N];
int n, m, s, t;

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
    adj[u][v] = adj[v][u] = true;
}
void bfs(int st, int* d){
    fill(d, d + n + 1, INF);
    d[st] = 0;
    queue<int> que;
    que.push(st);
    
    while(!que.empty()){
        int v = que.front(); que.pop();
        for(int i = 0; i < G[v].size(); i++){
            int u = G[v][i];
            if(d[u] > d[v] + 1){
                d[u] = d[v] + 1;
                que.push(u);
            }
        }
    }
}
int solve(){
    bfs(s, ds);
    bfs(t, dt);
    int res = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            res += !adj[i][j] && min(ds[i] + 1 + dt[j], ds[j] + 1 + dt[i]) >= ds[t];
        }
    }
    return res;
}
int main(){
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d\n", &u, &v);
        add_edge(u, v);
    }
    printf("%d\n", solve());
    return 0;
}