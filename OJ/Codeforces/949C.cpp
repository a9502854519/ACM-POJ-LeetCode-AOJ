#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define INF 1E9
#define MAX_V 100000 + 10

using namespace std;

int V, m, h;
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
vector<int> cmp_v[MAX_V];
bool used[MAX_V];
int cmp[MAX_V];
int u[MAX_V], out[MAX_V];

void add_edge(int from, int to){
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs(int v){
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        if(!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
}
void rdfs(int v, int k){
    used[v] = true;
    cmp[v] = k;
    cmp_v[k].push_back(v);
    for(int i = 0; i < rG[v].size(); i++){
        if(!used[rG[v][i]]) rdfs(rG[v][i], k);
        else if(cmp[rG[v][i]] != k){
            out[cmp[rG[v][i]]]++;
        }
    }
}
int scc(){
    memset(used, false, sizeof(used));
    memset(out, false, sizeof(out));
    vs.clear();
    for(int v = 0; v < V; v++){
        if(!used[v]) dfs(v);
    }
    memset(used, false, sizeof(used));
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--){
        if(!used[vs[i]]) rdfs(vs[i], k++);
    }
    return k;
}
void solve(){
    int k = scc();
    int res = -1;
    for(int i = 0; i < k; i++){
        if(out[i] == 0 && (res == -1 || cmp_v[i].size() < cmp_v[res].size())){
            res = i;
        }
    }
    cout << cmp_v[res].size() << endl;
    for(int i = 0; i < cmp_v[res].size(); i++){
        printf("%d%c", cmp_v[res][i] + 1, i == cmp_v[res].size() - 1 ? '\n' : ' ');
    }
}
int main(){
    cin >> V >> m >> h;
    for(int i = 0; i < V; i++){
        scanf("%d", u + i);
    }
    for(int i = 0; i < m; i++){
        int c1, c2;
        scanf("%d %d\n", &c1, &c2);
        c1--; c2--;
        if((u[c1] + 1) % h == u[c2]){
            add_edge(c1, c2);
        }
        if((u[c2] + 1) % h == u[c1]){
            add_edge(c2, c1);
        }
    }
    solve();
}