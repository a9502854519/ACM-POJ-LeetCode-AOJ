#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<ctime>
#include<cmath>
#include<utility>
#define MAX_V 1000000 + 50
#define MAX_E 1000000
#define INF 1e18
// #define DEBUG

using namespace std;
typedef long long ll;
typedef pair<ll, int> P;

#ifdef DEBUG
    using std::clock;
    using std::clock_t;
    clock_t S1, S2, F1, F2;
#endif

struct edge{
    int to;
    ll cost;
    edge() {}
    edge(int to, ll cost) : to(to), cost(cost) {}
};

int V, E;
vector<edge> G[2 * MAX_V];
vector<edge> rG[MAX_V];
vector<int> vs;
bool used[2 * MAX_V];
int cmp[MAX_V];
int parent[MAX_V];
ll dp[2 * MAX_V];

void add_edge(int from, int to, ll cost){
    G[from].push_back(edge(to, cost));
    rG[to].push_back(edge(from, cost));
}
void dfs(int v){
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        edge e = G[v][i];
        if(!used[e.to]) dfs(e.to);
    }
    vs.push_back(v);
}
void rdfs(int v, int k){
    used[v] = true;
    cmp[v] = k;
    for(int i = 0; i < rG[v].size(); i++){
        edge e = rG[v][i];
        if(!used[e.to]) rdfs(e.to, k);
    }
}
ll calc(ll y){
    ll n = (-1 + sqrt(1 + 8 * y)) / 2;
    return (n + 1) * y - (n * (n + 1) * (n + 2)) / 6;
}
ll collect(int p, int v, vector<edge>& tmp){
    used[v] = true;
    parent[v] = p;
    ll res = 0;
    for(int i = 0; i < G[v].size(); i++){
        edge e = G[v][i];
        if(cmp[e.to] != cmp[v]){
            tmp.push_back(e);
        }else{
            res += calc(e.cost);
        }
    }
    for(int i = 0; i < rG[v].size(); i++){
        edge e = rG[v][i];
        if(!used[e.to]){
            res += collect(p, e.to, tmp);
        }
    }
    G[v].clear();
    return res;
}
int scc(){
    memset(used, false, sizeof(used));
    vs.clear();
    for(int v = 0; v < V; v++){
        if(!used[v]) dfs(v);
    }
    memset(used, false, sizeof(used));
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--){
        if(!used[vs[i]]) rdfs(vs[i], k++);
    }
    // compress every component into a vertex
    memset(used, false, sizeof(used));
    for(int i = vs.size() - 1; i >= 0; i--){
        if(!used[vs[i]]){
            vector<edge> tmp;
            ll res = collect(vs[i], vs[i], tmp);
            for(int j = 0; j < tmp.size(); j++){
                G[vs[i] + V].push_back(tmp[j]);
            }
            G[vs[i]].push_back(edge(vs[i] + V, res));
        }
    }
    for(int v = V; v < 2 * V; v++){
        for(int i = 0; i < G[v].size(); i++){
            edge &e = G[v][i];
            e.to = parent[e.to];
        }
    }
    
    return k;
}
ll solve(){
    scc(); 
    int s;
    cin >> s;
    s = parent[s - 1];
    fill(dp, dp + 2 * V, INF);
    vs.clear();
    memset(used, false, sizeof(used));
    dfs(s);

    dp[s] = 0;
    ll res = INF;
    for(int i = vs.size() - 1; i >= 0; i--){
        int v = vs[i];
        for(int j = 0; j < G[v].size(); j++){
            edge e = G[v][j];
            if(dp[e.to] > dp[v] - e.cost){
                dp[e.to] = dp[v] - e.cost;
                if(dp[e.to] < res) res = dp[e.to];
            }
        }
    }
    return -res; 
}
int main(){
#ifdef DEBUG
    S1 = clock();
#endif
    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int u, v;
        ll cost;
        scanf("%d %d %I64d\n", &u, &v, &cost);
        add_edge(u - 1, v - 1, cost);
    }
#ifdef DEBUG
    F1 = clock();
    S2 = clock();
#endif
    cout << solve() << endl;
#ifdef DEBUG
    F2 = clock();
    cout << "Total I/O time is " << (double)(F1 - S1) / CLOCKS_PER_SEC << endl;
    cout << "Total processing time is " << (double)(F2 - S2) / CLOCKS_PER_SEC << endl;
#endif
    return 0;
}
