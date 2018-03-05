#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 100000 + 100

using namespace std;

int n;
vector<int> G[MAX_N];
int depth[MAX_N];

void add_edge(int p, int v){
    G[p].push_back(v);
}
void dfs(int v, int d){
    depth[d]++;
    for(int i = 0; i < G[v].size(); i++){
        dfs(G[v][i], d + 1);
    }
}
int solve(){
    memset(depth, 0, sizeof(depth));
    dfs(1, 0);
    int res = 0;
    for(int i = 0; i < n; i++){
        res += (depth[i] & 1);
    }
    return res;
}
int main(){
    cin >> n;
    for(int i = 2; i <= n; i++){
        int p;
        scanf("%d", &p);
        add_edge(p, i);
    }
    cout << solve() << endl;
    return 0;
}