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
#define MAX_N 100000 + 10
#define MAX_DAT_SIZE (1 << 18) - 1

using namespace std;

int n, q;
int a[MAX_N];
double dat[MAX_DAT_SIZE];
double add[MAX_DAT_SIZE];
double mul[MAX_DAT_SIZE];
int dat_size;

void update(int x, double v){
    int k = x + dat_size - 1;
    dat[k] += v;
    while(k > 0){
        k = (k - 1) / 2;
        dat[k] += v;
    }
}
void init(){
    dat_size = 1;
    while(dat_size < n) dat_size <<= 1;
    for(int i = 0; i < 2 * dat_size - 1; i++){
        mul[i] = 1.0;
        add[i] = 0.0;
    }
    for(int i = 0; i < n; i++) update(i, a[i]);
}
void propagate(int k, int l, int r){
    int lch = 2 * k + 1, rch = 2 * k + 2;
    if(add[k] != 0.0 || mul[k] != 1.0){
        dat[k] = dat[k] * mul[k] + add[k] * (r - l);
        if(r - l > 1){
            add[lch] = add[lch] * mul[k] + add[k];
            add[rch] = add[rch] * mul[k] + add[k];
            mul[lch] *= mul[k];
            mul[rch] *= mul[k];
        }
        add[k] = 0.0;
        mul[k] = 1.0;
    }
}
void update(int a, int b, int k, int l, int r, double x, double y){
    int lch = 2 * k + 1, rch = 2 * k + 2;
    propagate(k, l, r);
    
    if(r <= a || b <= l) return;
    if(a <= l && r <= b){
        dat[k] = dat[k] * y + x * (r - l);
        if(r - l > 1){
            add[lch] = add[lch] * y + x;
            add[rch] = add[rch] * y + x;
            mul[lch] *= y;
            mul[rch] *= y;
        }
    }else{
        update(a, b, lch, l, (l + r) / 2, x, y);
        update(a, b, rch, (l + r) / 2, r, x, y);
        dat[k] = dat[lch] + dat[rch];
    }
}
void update(int a, int b, double x, double y){
    update(a, b, 0, 0, dat_size, x, y);
}
double query(int a, int b, int k, int l, int r){
    propagate(k, l, r);
    
    if(r <= a || b <= l) return 0.0;
    if(a <= l && r <= b){
        return dat[k];
    }
    return query(a, b, 2 * k + 1, l, (l + r) / 2) + query(a, b, 2 * k + 2, (l + r) / 2, r);
}
double query(int a, int b){
    return query(a, b, 0, 0, dat_size);
}

void solve(){
    init();
    int t;
    int l1, r1, l2, r2;
    int cnt = 0;
    while(q--){
        scanf("%d", &t);
        if(t == 1){
            scanf("%d %d %d %d\n", &l1, &r1, &l2, &r2);
            double m1 = r1 - l1 + 1, m2 = r2 - l2 + 1;
            double E2 = query(l2 - 1, r2) / m2;
            double E1 = query(l1 - 1, r1) / m1;
            update(l1 - 1, r1, E2 / m1, 1.0 - 1.0 / m1);
            update(l2 - 1, r2, E1 / m2, 1.0 - 1.0 / m2);
        }else{
            scanf("%d %d\n", &l1, &r1);
            printf("%.10lf\n", query(l1 - 1, r1));
        }
    }
}
int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}