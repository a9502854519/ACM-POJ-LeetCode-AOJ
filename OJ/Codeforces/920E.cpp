#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
#include<cstring>
#include<utility>
#define MAX_N 200000 + 40

using namespace std;
typedef pair<int, int> P;

int n, m;
set<int> G[MAX_N];
set<int> vertex;

void add_edge(int u, int v){
    G[u].insert(v);
    G[v].insert(u);
}
void dfs(int v, int& cnt){
    vertex.erase(v);
    ++cnt;
    while(true){
        set<int>::iterator it = vertex.begin();
        while(it != vertex.end() && G[v].find(*it) != G[v].end()){
            ++it;
        }
        if(it == vertex.end()) break;
        dfs(*it, cnt);
    }
}
void solve(){
    for(int i = 1; i <= n; i++){
        vertex.insert(i);
    }
    int res = 0;
    vector<int> ps;
    while(vertex.size() > 0){
        int tmp = 0;
        dfs(*vertex.begin(), tmp);
        res++;
        ps.push_back(tmp);
    }
    cout << res << endl;
    sort(ps.begin(), ps.end());
    for(int i = 0; i < ps.size(); i++) cout << ps[i] << " ";
    cout << endl;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d\n", &x, &y);
        add_edge(x, y);
    }
    solve();
    return 0;
}