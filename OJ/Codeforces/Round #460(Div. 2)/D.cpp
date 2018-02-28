#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAX_N 300000 + 10

using namespace std;

int n, m;
vector<int> G[MAX_N];
vector<int> vs;
char s[MAX_N];
int color[MAX_N];
int ct[MAX_N][26];

void add_edge(int u, int v){
    G[u].push_back(v);
}
bool dfs(int v){
    color[v] = 1; // GRAY
    for(int i = 0; i < G[v].size(); i++){
        int u = G[v][i];
        if(color[u] == 0){
            if(!dfs(u)) return false;
        }else if(color[u] == 1) return false;
    }
    color[v] = 2;
    vs.push_back(v);
    return true;
}
int compare(int v, int u){
    int mx = 0;
    for(int i = 0; i < 26; i++){
        ct[v][i] = max(ct[v][i], ct[u][i]);
        mx = max(ct[v][i], mx);
    }
    return mx;
}
int solve(){
    memset(color, 0, sizeof(color)); //WHITE
    for(int i = 0; i < n; i++){
        if(color[i] == 0){
            if(!dfs(i)) return -1;
        }
    }
    int res = 0;
    memset(color, 0, sizeof(color));
    memset(ct, 0, sizeof(ct));
    for(int k = 0; k < vs.size(); k++){
        int v = vs[k];
        for(int i = 0; i < G[v].size(); i++){
            res = max(res, compare(v, G[v][i]));
        }
        res = max(res, ++ct[v][s[v] - 'a']);
    }
    return res;
}
int main(){
    cin >> n >> m;
    scanf("%s", s);
    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d\n", &x, &y);
        add_edge(x - 1, y - 1);
    }
    cout << solve() << endl;
    return 0;
}