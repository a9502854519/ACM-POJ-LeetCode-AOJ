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

using namespace std;
typedef long long ll;

const ll M = 1e9 + 9;
ll n, a, b, k;
string s;

ll pow(ll a, ll b){
    ll res = 1, A = a;
    while(b > 0){
        if(b & 1) res = res * A % M;
        A = A * A % M;
        b >>= 1;
    }
    return res;
}
void solve(){
    ll tmp = 0, inv = pow(a, M - 2), A = pow(a, n), B = 1;
    for(int i = 0; i < k; i++){
        tmp = (tmp + (s[i] == '+' ? 1 : -1) * A % M * B % M) % M;
        A = A * inv % M;
        B = B * b % M;
    }
    
    ll r = pow(inv * b % M, k);
    ll res;
    if(r != 1) res = tmp * (pow(r, (n + 1) / k) - 1) % M * pow(r - 1, M - 2) % M;
    else res = tmp * ((n + 1) / k) % M;
    cout << (res + M) % M << endl;
}
int main(){
    cin >> n >> a >> b >> k >> s;
    solve();
    return 0;
}