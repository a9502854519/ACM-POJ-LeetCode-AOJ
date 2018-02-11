#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 500

using namespace std;

int V, E;
vector<int> G[MAX_V];
vector<int> vs, es, edge_set;
bool d[MAX_V], f[MAX_V];

void add_edge(int from, int to){
    G[from].push_back(to);
}

void dfs(int v){
    d[v] = true;
    es.push_back(v);
    for(int i = 0; i < G[v].size(); i++){
        if(!d[G[v][i]]) dfs(G[v][i]);
        else if(!f[G[v][i]] && (vs.size() == 0 || vs.back() != v)){
            vs.push_back(v);
            if(edge_set.size() == 0){
                int k = 0;
                while(es[k] != G[v][i]) k++;
                do edge_set.push_back(es[k]); while(es[k++] != v);
                edge_set.push_back(G[v][i]);
            }
        }
    }
    es.pop_back();
    f[v] = true;
}
bool dfs(int v, int ru, int rv){
    d[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        if(v == ru && G[v][i] == rv) continue;
        if(!d[G[v][i]]){
            if(!dfs(G[v][i], ru, rv)) return false;
        }else if(d[G[v][i]] && !f[G[v][i]]){
            return false;
        }
    }
    f[v] = true;
    return true;
}
void solve(){
    memset(f, false, sizeof(f));
    memset(d, false, sizeof(d));
    for(int v = 0; v < V; v++){
        if(!d[v]) dfs(v);
    }
    for(int i = 0; i < edge_set.size() - 1; i++){
            memset(d, false, sizeof(d));
            memset(f, false, sizeof(f));
            bool ok = true;
            
            for(int k = 0; k < vs.size(); k++){
                if(!d[vs[k]]){
                    ok &= dfs(vs[k], edge_set[i], edge_set[i + 1]);
                    if(!ok) break;
                }
            }
            if(ok){
                cout << "YES\n";
                return;
            }
    }
    cout << "NO\n";
}
int main(){
    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int u, v;
        scanf("%d %d\n", &u, &v);
        add_edge(u - 1, v - 1);
    }
    solve();
    return 0;
}