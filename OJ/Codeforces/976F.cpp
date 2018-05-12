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
#include<vector>
#include<cmath>
#include<utility>
#include<queue>
#include<set>
#include<cstring>
#include<algorithm>
#define MAX_N 4000 + 100

using namespace std;

struct edge{
    int to, cap, rev, id;
    edge() {}
    edge(int to, int cap, int rev, int id) : to(to), cap(cap), rev(rev), id(id) {}
};
int n1, n2, m;
vector<edge> G[MAX_N];
bool used[MAX_N];
int cover[MAX_N];

void add_edge(int from, int to, int cap, int id){
    G[from].push_back(edge(to, cap, G[to].size(), id));
    G[to].push_back(edge(from, 0, G[from].size() - 1, id));
}
int dfs(int v, int t, int f){
    if(v == t) return f;
    used[v] = true;
    for(auto& e : G[v]){
        if(!used[e.to] && e.cap > 0){
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s, int t){
    int flow = 0;
    while(true){
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, 1e9);
        if(f == 0) return flow;
        flow += f;
    }
}
void solve(){
    int s = 0, t = n1 + n2 + 1;
    for(int i = 1; i <= n1; i++) add_edge(s, i, 1, -1);
    for(int i = n1 + 1; i <= n1 + n2; i++) add_edge(i, t, 1, -1);
    
    int mindegree = 1e9;
    for(int i = 1; i <= n1 + n2; i++){
        if(G[i].size() - 1 < mindegree) mindegree = G[i].size() - 1;
    }
    printf("0\n");
    for(int d = 1; d <= mindegree; d++){
        max_flow(s, t);
        vector<int> res;
        memset(cover, 0, sizeof(cover));
        for(int v = 1; v <= n1 + n2; v++){
            if(v <= n1){
                for(auto& e : G[v]){
                    if(e.to != s && e.cap == 0){
                        res.push_back(e.id);
                        cover[v]++;
                        cover[e.to]++;
                    }
                }
            }
            if(cover[v] < d){
                for(int i = 0; i < G[v].size() && cover[v] < d; i++){
                    edge& e = G[v][i];
                    if((v <= n1 && e.to != s && e.cap == 1) || (e.to != t && e.cap == 0)){
                        res.push_back(e.id);
                        cover[v]++;
                    }
                }
            }
        }
        printf("%d ", res.size());
        for(auto& v : res) printf("%d ", v);
        cout << endl;
        
        for(auto& e : G[s]) e.cap++;
        for(auto& e : G[t]) G[e.to][e.rev].cap++;
    }
}
int main(){
    cin >> n1 >> n2 >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d\n", &u, &v);
        add_edge(u, v + n1, 1, i + 1);
    }
    solve();
    return 0;
}