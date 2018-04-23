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
#define MAX_N 200000 + 100

using namespace std;

int n, degree[MAX_N];
bool ok[MAX_N];
vector<int> G[MAX_N];

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
    degree[u]++;
    degree[v]++;
}
bool dfs(int v, int p){
    int cnt = 0;
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p){
            cnt += !dfs(G[v][i], v);
        }
    }
//    printf("degree[%d] = %d   cnt = %d\n", v, degree[v], cnt);
    ok[v] = (degree[v] - cnt) % 2;
    return ok[v];
}
void output(int v, int p){
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p && !ok[G[v][i]]){
            output(G[v][i], v);
        }
    }
    printf("%d\n", v);
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p && ok[G[v][i]]){
            output(G[v][i], v);
        }
    }
}
void solve(){
    if(!dfs(1, -1)){
        puts("YES");
        output(1, -1);
    }else{
        puts("NO");
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int p;
        scanf("%d", &p);
        if(p) add_edge(i + 1, p);
    }
    solve();
    return 0;
}