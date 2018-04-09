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
#define MAX_N 1000000

using namespace std;
typedef long long ll;

const ll MOD = 1000000000 + 7;
string a, b;
ll fac[MAX_N + 1];
ll rev[MAX_N + 1];
ll cnt[26];
ll f[26];

ll pow(ll x, ll y){
    ll res = 1, A = x;
    while(y > 0){
        if(y & 1) res = res * A % MOD;
        A = A * A % MOD;
        y >>= 1;
    }
    return res;
}
void init(){
    fac[0] = 1;
    rev[0] = 1;
    for(int i = 1; i <= MAX_N; i++){
        fac[i] = fac[i - 1] * i % MOD;
        rev[i] = pow(fac[i], MOD - 2);
    }
}
void restore(){
    for(int i = 0; i < 26; i++) f[i] = cnt[i];
}
void solve(){
    init();
    for(int i = 0; i < a.length(); i++){
        cnt[a[i] - 'a']++;
    }
    
    ll res = 0;
    restore();
    for(int i = 0; i < a.length(); i++){
        ll tmp = fac[a.length() - i - 1];
        for(int j = 0; j < 26; j++){
            tmp = tmp * rev[f[j]] % MOD;
        }
        for(int j = a[i] - 'a' + 1; j < 26; j++){
            res = (res + tmp * f[j] % MOD) % MOD;
        }
        f[a[i] - 'a']--;
    }
    restore();
    for(int i = 0; i < b.length(); i++){
        ll tmp = fac[b.length() - i - 1];
        for(int j = 0; j < 26; j++){
            tmp = tmp * rev[f[j]] % MOD;
        }
        for(int j = 0; j < b[i] - 'a'; j++){
            res = (res + tmp * f[j] % MOD) % MOD;
        }
        if(f[b[i] - 'a'] > 0) f[b[i] - 'a']--;
        else break;
    }
    ll total = fac[a.length()];
    for(int i = 0; i < 26; i++) total = total * rev[cnt[i]] % MOD;
    cout << ((res - total) % MOD + MOD) % MOD << endl;
}
int main(){
    cin >> a >> b;
    solve();
    return 0;
}