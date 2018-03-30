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
#define MAX_N 500000 + 100

using namespace std;
typedef long long ll;

int n, r;
ll k;
ll a[MAX_N];
ll b[MAX_N];

bool check(ll x){
    memcpy(b, a, n * 8);
    ll df = 0, res = 0;
    for(int i = 0; i < r; i++) df += b[i];
    for(int i = 0; i < n; i++){
        if(i + r < n) df += b[i + r];
        if(i - r > 0) df -= b[i - r - 1];
        
        if(df < x){
            b[min(n - 1, i + r)] += x - df;
            if(res + x - df < res) return false; //overflow -> too large
            res += x - df;
            df = x;
        }
    }
    return res <= k;
}
ll solve(){
    ll ub, lb = 0, mid, sum = 0;
    for(int i = 0; i < min(2 * r + 1, n); i++) sum += a[i];
    ub = sum;
    for(int i = 2 * r + 1; i < n; i++){
        sum += a[i] - a[i - 2 * r - 1];
        ub = min(ub, sum);
    }
    ub += k + 1;
    while(ub - lb > 1){
        mid = (ub + lb) / 2;
        if(check(mid)) lb = mid;
        else ub = mid;
    }
    return lb;
}
int main(){
    cin >> n >> r >> k;
    for(int i = 0; i < n; i++) scanf("%I64d", a + i);
    cout << solve() << endl;
    return 0;
}