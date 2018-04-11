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
#define MAX_N 200000
#define MAX_DAT_SIZE (1 << 19) - 1

using namespace std;

int n, a[MAX_N];
vector<int> dat[MAX_DAT_SIZE];

void build(int k, int l, int r){
    if(r - l == 1){
        dat[k].push_back(a[l]);
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    build(lch, l, (l + r) / 2);
    build(rch, (l + r) / 2, r);
    dat[k].resize(r - l);
    merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
}
int query(int a, int b, int k, int l, int r, int v){
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b){
        return dat[k].end() - lower_bound(dat[k].begin(), dat[k].end(), v);
    }
    return query(a, b, 2 * k + 1, l, (l + r) / 2, v) + 
           query(a, b, 2 * k + 2, (l + r) / 2, r, v);
}
int query(int a, int b, int v){
    return query(a, b, 0, 0, n, v);
}
void solve(){
    build(0, 0, n);
    long long res = 0;
    for(int i = 1; i < n; i++){
        res += query(0, min(a[i], i), i + 1);
    }
    cout << res << endl;
    // cout << query(0, 1, 2) << endl;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}