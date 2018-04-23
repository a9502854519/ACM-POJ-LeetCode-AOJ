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
#include<cmath>
#include<algorithm>
#define MAX_N 200000 + 100
#define MAX_P 1000000 + 10

using namespace std;
typedef long long ll;

struct D{
    ll w, h, c;
    D() {}
    D(ll w, ll h, ll c) : w(w), h(h), c(c) {}
}d[MAX_N];
int n;

bool cmp(const D& a, const D& b){
    if(a.w != b.w) return a.w < b.w;
    return a.h < b.h;
}
ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
bool equal(ll a1, ll b1, ll a2, ll b2){
    double t1 = (double)a1 / (double)b1;
    double t2 = (double)a2 / (double)b2;
    return fabs(t1 - t2) < 1e-10;
}
int solve(){
    sort(d, d + n, cmp);
    vector<vector<D> > v;
    for(int i = 0; i < n; ){
        vector<D> tmp;
        do{
            tmp.push_back(d[i++]);
        }while(i < n && d[i].w == d[i - 1].w);
        
        if(v.size() > 0){
            if(tmp.size() != v[0].size()) return 0;
            else{
                for(int i = 0; i < tmp.size(); i++){
                    if(tmp[i].h != v[0][i].h) return 0;
                    if(i > 0 && !equal(tmp[i].c, tmp[i - 1].c, v[0][i].c, v[0][i - 1].c)) return 0;
                }
            }
        }
        v.push_back(tmp);
    }
    ll g1 = v[0][0].c, g2 = v[0][0].c, C = v[0][0].c;
    for(int i = 1; i < v.size(); i++){
        g1 = gcd(g1, v[i][0].c);
    }
    for(int i = 1; i < v[0].size(); i++){
        g2 = gcd(g2, v[0][i].c);
    }
    ll res = 0;
    for(ll i = 1; i * i <= g1; i++){
        if(g1 % i == 0){
            res += g2 % (C / i) == 0;
            if(i * i != g1) res += g2 % (C / (g1 / i)) == 0;
        }
    }
    return res;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%I64d %I64d %I64d\n", &d[i].w, &d[i].h, &d[i].c);
    }
    cout << solve() << endl;
    return 0;
}