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
#include<algorithm>
#define MAX_N 100000

using namespace std;

struct Data{
    int u, v, w;
    Data() {}
    Data(int u, int v, int w) : u(u), v(v), w(w) {}
}E[MAX_N];
int n, m, dp[MAX_N];
vector<int> dat[MAX_N];
vector<int> s[MAX_N];
int dat_size[MAX_N];

void init(){
    for(int i = 0; i < m; i++){
        s[E[i].v].push_back(E[i].w);
    }
    for(int i = 0; i < n; i++){
        if(s[i].size() > 0){
            int k = 1;
            while(k < s[i].size()) k <<= 1;
            dat_size[i] = k;
            dat[i].resize(2 * k - 1, 0);
            sort(s[i].begin(), s[i].end());
        }
    }
}
int query(vector<int>& tree, int a, int b, int k, int l, int r){
    if(b <= l || r <= a) return 0;
    else if(a <= l && r <= b) return tree[k];
    int r1 = query(tree, a, b, 2 * k + 1, l, (l + r) / 2);
    int r2 = query(tree, a, b, 2 * k + 2, (l + r) / 2, r);
    return max(r1, r2);
}
int query(int v, int w){
    int i = lower_bound(s[v].begin(), s[v].end(), w) - s[v].begin();
    return query(dat[v], 0, i, 0, 0, dat_size[v]);
}
void update(int v, int w, int val){
    int i = lower_bound(s[v].begin(), s[v].end(), w) - s[v].begin() + dat_size[v] - 1;
    vector<int>& tree = dat[v];
    tree[i] = val;
    while(i > 0){
        i = (i - 1) / 2;
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }
}
void solve(){
    init();
    int res = 0;
    for(int i = 0; i < m; i++){
        int u = E[i].u, v = E[i].v, w = E[i].w;
        int tmp = query(u, w);
        res = max(res, tmp + 1);
        update(v, w, tmp + 1);
    }
    cout << res << endl;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d\n", &E[i].u, &E[i].v, &E[i].w);
        E[i].u--;
        E[i].v--;
    }
    solve();
    return 0;
}