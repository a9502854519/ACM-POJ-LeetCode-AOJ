#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<utility>
#define MAX_V 100 + 10
#define INF 0x3f3f3f3f

using namespace std;
typedef pair<int, int> P;

int V, s;
vector<int> G[MAX_V];
int d[MAX_V];

void add_edge(int u, int v){
    G[u].push_back(v);
}
void init(){
    for(int i = 1; i <= V; i++){
        G[i].clear();
    }
    memset(d, 0x3f, sizeof(d));
}
void solve(){
    priority_queue<P, vector<P>, greater<P> > que;
    d[s] = 0;
    que.push(make_pair(d[s], s));
    while(!que.empty()){
        P p = que.top(); que.pop();
        int v = p.second;
        if(p.first > d[v]) continue;
        
        for(int i = 0; i < G[v].size(); i++){
            int u = G[v][i];
            if(d[u] > d[v] - 1){
                d[u] = d[v] - 1;
                que.push(make_pair(d[u], u));
            }
        }
    }
    int res = INF, res_v = INF;
    for(int i = 1; i <= V; i++){
        if(res > d[i]){
            res = d[i];
            res_v = i;
        }else if(res == d[i] && i < res_v) res_v = i;
    }
    printf("The longest path from %d has length %d, finishing at %d.\n\n", s, -res, res_v);
}
int main(){
    int Case = 1;
    while(cin >> V && V){
        init();
        cin >> s;
        int u, v;
        while(cin >> u >> v && (u || v)){
            add_edge(u, v);
        }
        printf("Case %d: ", Case++);
        solve();
    }
}