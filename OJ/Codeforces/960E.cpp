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
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_N 200000 + 100

using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7e0;
int n;
vector<int> G[MAX_N];
ll V[MAX_N];
ll dp[MAX_N][2];
ll cnt[MAX_N][2];

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
void calc(int v, int p, int k, ll& res){
    ll sum_cnt = 0, sum_dp = 0;
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p){
            sum_cnt += cnt[G[v][i]][k];
            sum_dp = (sum_dp + dp[G[v][i]][k]) % MOD;
        }
    }
    cnt[v][1 - k] = (cnt[v][1 - k] + sum_cnt % MOD);
    if(k == 1) res = ((res + sum_cnt * V[v] % MOD + sum_dp) % MOD + MOD) % MOD;
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p){
            int u = G[v][i];
            sum_cnt -= cnt[u][k];
            sum_dp = ((sum_dp - dp[u][k]) % MOD + MOD) % MOD;
            res = (res + dp[u][k] * sum_cnt % MOD + sum_dp * cnt[u][k] % MOD + (k ? 1 : -1) * V[v] * cnt[u][k] % MOD * sum_cnt % MOD) % MOD;
            res = (res + MOD) % MOD;
            dp[v][1 - k] = ((dp[v][1 - k] + dp[u][k]) % MOD + (k ? 1 : -1) * V[v] * cnt[u][k] % MOD) % MOD;
            dp[v][1 - k] = (dp[v][1 - k] + MOD) % MOD;
        }
    }
}
void dfs(int p, int v, ll& res){
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p) dfs(v, G[v][i], res);
    }
    calc(v, p, 0, res);
    calc(v, p, 1, res);
}
void solve(){
    ll res = 0;
    for(int i = 1; i <= n; i++){
        dp[i][0] = V[i];
        cnt[i][0] = 1;
    }
    dfs(-1, 1, res);
    res = res * 2 % MOD;
    for(int i = 1; i <= n; i++) res = (res + V[i]) % MOD;
    res = (res + MOD) % MOD;
    cout << res << endl;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%I64d", V + i);
    
    for(int i = 0; i < n - 1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    solve();
    return 0;
}