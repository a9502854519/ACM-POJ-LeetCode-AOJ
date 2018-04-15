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
#define MAX_N 150000 + 100
#define MAX_DAT_SIZE (1 << 19) - 1
#define INF 1e16

using namespace std;
typedef long long ll;

ll n, a[MAX_N], b[MAX_N];
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
    if(a[i] > a[j]) dat[k] = j;
    else dat[k] = i;
}
void update(int k, int l, int r, int i, ll v){
    if(i < l || r <= i) return;
    if(r - l == 1){
        a[i] = v;
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    update(lch, l, (l + r) / 2, i, v);
    update(rch, (l + r) / 2, r, i, v);
    int x = dat[lch], y = dat[rch];
    if(a[x] > a[y]) dat[k] = y;
    else dat[k] = x;
}
int query(int s, int t, int k, int l, int r){
    if(r <= s || t <= l) return -1;
    if(s <= l && r <= t){
        return dat[k];
    }
    
    int i = query(s, t, 2 * k + 1, l, (l + r) / 2);
    int j = query(s, t, 2 * k + 2, (l + r) / 2, r);
    if(i == -1) return j;
    else if(j == -1) return i;
    else return a[i] > a[j] ? j : i;
}
void update(int i, ll v){
    update(0, 0, n, i, v);
}
int query(int s, int t){
    return query(s, t, 0, 0, n);
}
void solve(){
    build(0, 0, n);
    int cnt = n;
    for(;;){
        int i = query(0, n);
        if(a[i] == INF) break;
        
        int j = query(i + 1, n);
        
        if(j == -1 || a[i] != a[j]){
            b[i] = a[i];
        }
        else{
            cnt--;
            b[i] = -1;
            update(j, 2 * a[j]);
        }
       
        update(i, INF);
    }
    cout << cnt << endl;
    for(int i = 0; i < n; i++){
        if(b[i] != -1) cout << b[i] << " ";
    }
    cout << endl;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}