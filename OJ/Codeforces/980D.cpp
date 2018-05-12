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
#include<cmath>
#include<map>
#include<cstring>
#include<vector>
#define MAX_N 5010
#define MAX_PRIME 10001

using namespace std;
typedef long long ll;

ll n, a[MAX_N];
int cnt[MAX_N], dp[MAX_N], p[MAX_N];
bool is_prime[MAX_PRIME], zero[MAX_N];
vector<ll> prime;
map<ll, int> mp;

void init(){
    fill(is_prime, is_prime + MAX_PRIME, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 0; i < MAX_PRIME; i++){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j = i * 2; j < MAX_PRIME; j += i) is_prime[j] = false;
        }
    }
}
ll rebuild(ll v){
    if(v == 0) return 0;
    ll res = 1;
    if(v < 0){
        res = -1;
        v = -v;
    }
    for(int i = 0; prime[i] * prime[i] <= v && i < prime.size(); i++){
        if(v % prime[i] == 0){
            int cnt = 0;
            while(v % prime[i] == 0) cnt++, v /= prime[i];
            if(cnt % 2) res *= prime[i];
        }
    }
    if(v > 1) res *= v;
    return res;
}
void solve(){
    init();
    for(int i = 1; i <= n; i++){
        a[i] = rebuild(a[i]);
        if(a[i] == 0) p[i] = i - 1, zero[i] = true;
        else if(mp.find(a[i]) != mp.end()) p[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    fill(zero, zero + n + 1, true);
    for(int k = 1; k <= n; k++){
        for(int i = n; i >= k; i--){
            dp[i] = dp[i - 1] + (p[i] < (i - k + 1) && (k == 1 || !zero[i - 1]));
            cnt[dp[i]]++;
            zero[i] = (a[i] == 0 && zero[i - 1]);
        }
    }
    for(int i = 1; i <= n; i++) printf("%d ", cnt[i]);
    cout << endl;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%I64d", a + i);
    solve();
    return 0;
}