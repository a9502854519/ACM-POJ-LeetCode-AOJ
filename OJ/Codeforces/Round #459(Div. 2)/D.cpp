#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 100

using namespace std;

struct edge{
    int to, cost;
    edge() {}
    edge(int to, int cost) : to(to), cost(cost) {}
};
int V, E;
vector<edge> G[MAX_V];
vector<int> vs;
bool used[MAX_V];
bool res[MAX_V][MAX_V];
int move[MAX_V][MAX_V];

void add_edge(int from, int to, int cost){
    G[from].push_back(edge(to, cost));
}
void dfs(int v){
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        if(!used[G[v][i].to]) dfs(G[v][i].to);
    }
    vs.push_back(v);
}
void solve(){
    memset(used, false, sizeof(used));
    memset(move, -1, sizeof(move));
    for(int i = 0; i < V; i++){
        if(!used[i]) dfs(i);
    }
    for(int i = 0; i < vs.size(); i++){
        for(int j = 0; j < vs.size(); j++){
            int u = vs[i], v = vs[j];
            bool tmp = false;
            for(int m = 0; m < G[u].size(); m++){
                edge M = G[u][m];
                bool tmp2 = true;
                for(int n = 0; n < G[v].size() && tmp2; n++){
                    edge L = G[v][n];
                    tmp2 &= (M.cost > L.cost) || ((res[M.to][L.to]) && move[M.to][L.to] >= L.cost);
                }
                tmp |= tmp2;
                if(tmp2 == true) move[u][v] = max(move[u][v], M.cost);
            }
            res[u][v] = tmp;
        }
    }
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            printf("%c", res[i][j] ? 'A' : 'B');
        }
        cout << endl;
    }
}
int main(){
    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int from, to;
        char cost;
        scanf("%d %d %c\n", &from, &to, &cost);
        add_edge(from - 1, to - 1, cost - 'a');
    }
    solve();   
}