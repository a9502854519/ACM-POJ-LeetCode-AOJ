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
#include<cstring>
#include<algorithm>
#define MAX_N 100010
#define MAX_DAT_SIZE (1 << 18) - 1

using namespace std;

int n, m, dat_size;
int dat[MAX_DAT_SIZE], lazy[MAX_DAT_SIZE];
int dp[2][MAX_N], lis[MAX_N];

void prop(int k, int l, int r){
    int lch = 2 * k + 1, rch = 2 * k + 2;
    if(lazy[k] != 0){
        dat[k] += lazy[k];
        if(r - l > 1){
            lazy[lch] += lazy[k];
            lazy[rch] += lazy[k];
        }
        lazy[k] = 0;
    }
}
void update(int a, int b, int k, int l, int r, int v){
    int lch = 2 * k + 1, rch = 2 * k + 2;
    prop(k, l, r);
    if(a >= r || b <= l) return;
    else if(a <= l && r <= b){
        lazy[k] += v;
    }else{
        update(a, b, lch, l, (l + r) / 2, v);
        update(a, b, rch, (l + r) / 2, r, v);
    }
}
void update(int a, int b, int v){
    update(a, b, 0, 0, dat_size, v);
}
int query(int a, int b, int k, int l, int r){
    int lch = 2 * k + 1, rch = 2 * k + 2;
    prop(k, l, r);
    if(a >= r || b <= l) return 0;
    else if(a <= l && r <= b){
        return dat[k];
    }else{
        return query(a, b, lch, l, (l + r) / 2) + 
               query(a, b, rch, (l + r) / 2, r);
    }
}
int query(int a, int b){
    return query(a, b, 0, 0, dat_size);
}
void solve(){
    memset(lis, 0x3f, sizeof(lis));
    for(int i = 0; i < m; i++){
        int v = query(i, i + 1);
        int* j = upper_bound(lis, lis + m, v);
        dp[0][i] = j - lis + 1;
        *j = v;
    }
    memset(lis, 0x3f, sizeof(lis));
    for(int i = m - 1; i >= 0; i--){
        int v = query(i, i + 1);
        int* j = upper_bound(lis, lis + m, v);
        dp[1][i] = j - lis + 1;
        *j = v;
    }
    int res = 0;
    for(int i = 0; i < m; i++) res = max(res, dp[0][i] + dp[1][i] - 1);
    cout << res << endl;
}
void init(){
    dat_size = 1;
    while(dat_size < m) dat_size <<= 1;
}
int main(){
    cin >> n >> m;
    init();
    for(int i = 0; i < n; i++){
        int l, r;
        scanf("%d %d\n", &l, &r);
        update(l - 1, r, 1);
    }
    solve();
    return 0;
}