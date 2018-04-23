//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永無BUG
//
//
//
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define MAX_N 100000 + 100

using namespace std;

struct edge{
    int to, id;
    edge() {}
    edge(int to, int id) : to(to), id(id) {}
};
int n, m;
vector<edge> G[MAX_N];
bool cycle[MAX_N];
bool used[MAX_N];
int depth[MAX_N];
int eid[MAX_N];
int cid[MAX_N];

void add_edge(int u, int v, int id){
    G[u].push_back(edge(v, id));
    G[v].push_back(edge(u, id));
}
void dfs(int v, int p, int d, int& cycle_cnt, vector<int>& ver){
    used[v] = true;
    depth[v] = d;
    ver.push_back(v);
    for(int i = 0; i < G[v].size(); i++){
        int to = G[v][i].to, id = G[v][i].id;
        if(to != p){
            eid[v] = id;
            if(!used[to]){
                dfs(to, v, d + 1, cycle_cnt, ver);
            }else if(depth[to] < d){
                cycle_cnt++;
                bool ok = true;
                for(int k = ver.size() - 1;; k--){
                    ok &= cid[eid[ver[k]]] == 0;
                    cycle[cid[eid[ver[k]]]] = false;
                    cid[eid[ver[k]]] = cycle_cnt;
                    if(ver[k] == to) break;
                }
                cycle[cycle_cnt] = ok;
            }
        }
    }
    ver.pop_back();
}
void solve(){
    int cycle_cnt = 0;
    vector<int> ver;
    vector<int> res;
    for(int i = 1; i <= n; i++){
        if(!used[i]) dfs(i, -1, 0, cycle_cnt, ver);
    }
    for(int i = 1; i <= m; i++){
        if(cid[i] > 0 && cycle[cid[i]]) res.push_back(i);
    }
    cout << res.size() << endl;
    for(int i = 0; i < res.size(); i++) printf("%d%c", res[i], i == res.size() - 1 ? '\n' : ' ');
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, i + 1);
    }
    solve();
    return 0;
}
