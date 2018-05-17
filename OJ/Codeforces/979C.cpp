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
#include<cstring>
#define MAX_N 300010

using namespace std;
typedef long long ll;

int x, y;
ll n;
vector<int> G[MAX_N];
ll cnt_x, cnt_y;

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
ll dfs(int p, int v){
    ll cnt = 1;
    for(int u : G[v]){
        if(u != p){
            ll tmp = dfs(v, u);
            if(tmp == -1){
                if(v == x) continue;
                else return -1;
            }
            cnt += tmp;
        }
    }
    if(v == x){
        cnt_x = cnt;
    }
    else if(v == y){
        cnt_y = cnt;
        cnt = -1;
    }
    return cnt;
}
void solve(){
   dfs(-1, x); 
   ll res = n * (n - 1) - cnt_x * cnt_y;
   cout << res << endl;
}
int main(){
    cin >> n >> x >> y;
    for(int i = 0; i < n - 1; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        add_edge(a, b);
    }
    solve();
    return 0;
}
