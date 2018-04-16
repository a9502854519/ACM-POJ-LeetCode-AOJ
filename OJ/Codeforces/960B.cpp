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
#define MAX_N 1000 + 10
#define MAX_DAT_SIZE 2048 - 1

using namespace std;
typedef long long ll;

int n, k1, k2;
ll a[MAX_N], b[MAX_N];
int dat[MAX_DAT_SIZE];

void build(int k, int l, int r){
    if(r - l == 1){
        dat[k] = l;
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    build(lch, l, (l + r) / 2);
    build(rch, (l + r) / 2, r);
    int i = dat[lch], j = dat[rch];
    if(a[i] <= a[j]) dat[k] = j;
    else dat[k] = i;
}
void update(int k, int l, int r, int i, int v){
    if(i < l || r <= i) return;
    if(r - l == 1){
        a[i] += v;
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    update(lch, l, (l + r) / 2, i, v);
    update(rch, (l + r) / 2, r, i, v);
    int x = dat[lch], y = dat[rch];
    if(a[x] <= a[y]) dat[k] = y;
    else dat[k] = x;
}
int query(int s, int t, int k, int l, int r){
    if(t <= l || r <= s) return -1;
    if(s <= l && r <= t) return dat[k];
    
    int r1 = query(s, t, 2 * k + 1, l, (l + r) / 2);
    int r2 = query(s, t, 2 * k + 2, (l + r) / 2, r);
    if(r1 == -1) return r2;
    else if(r2 == -1) return r1;
    else return a[r1] <= a[r2] ? r2 : r1;
}
void update(int i, int v){
    update(0, 0, n, i, v);
}
int query(int a, int b){
    return query(a, b, 0, 0, n);
}
void init(){
    for(int i = 0; i < n; i++) a[i] = abs(a[i] - b[i]);
    build(0, 0, n);
}
void solve(){
    init();
    for(int i = 0; i < k1 + k2; i++){
        int j = query(0, n);
        if(a[j] == 0) update(j, 1);
        else update(j, -1);
    }
    ll res = 0;
    for(int i = 0; i < n; i++){
        res += a[i] * a[i];
    }
    cout << res << endl;
}
int main(){
    cin >> n >> k1 >> k2;
    for(int i = 0; i < n; i++) scanf("%I64d", a + i);
    for(int i = 0; i < n; i++) scanf("%I64d", b + i);
    solve();
    return 0;
}