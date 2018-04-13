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

using namespace std;
typedef long long ll;

ll n, k, sum;
const ll MOD = 1000000000 + 7;

ll qmod(ll a, ll b){
    ll res = 1, A = a;
    while(b > 0){
        if(b & 1) res = res * A % MOD;
        A = A * A % MOD;
        b >>= 1;
    }
    return res;
}
ll S(ll n, ll m){
    ll res = 0, comb = 1;
    for(ll t = 0; t <= m; t++){
        res = (res + comb * (t % 2 == 0 ? 1 : -1) * qmod(m - t, n) % MOD) % MOD;
        comb = (comb * (m - t) % MOD) * qmod(t + 1, MOD - 2) % MOD;
    }
    ll tmp = 1;
    for(ll i = 1; i <= m; i++){
        tmp = tmp * i % MOD;
    }
    res = res * qmod(tmp, MOD - 2) % MOD;
    return (res % MOD + MOD) % MOD;
}
void solve(){
    ll res = (S(n, k) + (n - 1) * S(n - 1, k)) % MOD * sum % MOD;
    cout << res << endl;
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        ll a;
        scanf("%I64d", &a);
        sum = (sum + a) % MOD;
    }
    solve();
    return 0;
}