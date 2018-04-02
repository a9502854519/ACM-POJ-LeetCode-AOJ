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
#define MAX_N 5000 + 10

using namespace std;
typedef long long ll;

const ll M = 1000000000 + 7;
const ll rt = 500000004; // 2 ^ -1
ll n, a[MAX_N], dp[MAX_N][2], cnt[MAX_N];

void solve(){
   memset(dp, 0, sizeof(dp));
   for(int i = 1; i <= n; i++) dp[i][1] = cnt[i];
   
    for(int k = 0; k < 2 * n - 2; k++){
        for(int i = n; i >= (k + 1) / 2; i--){
            dp[i + 1][0] = dp[i][0] * a[i] % M;
            if(k & 1){
                dp[i + 1][0] = (dp[i + 1][0] + dp[i][1] * a[i] % M) % M;
                if(k == 1){
                    dp[i][1] = (a[i - 1] * (a[i - 1] - 1) / 2) % M * cnt[i - 1] % M;
                }else{
                    dp[i][1] = (dp[i][1] * a[i - 1] % M) * rt % M;
                }
            }else{
                dp[i + 1][1] = dp[i][1] * a[i] % M * (k == 0 ? 1 : 2) % M;
            }
        }
        ll res = 0;
        for(int i = 1; i <= n; i++){
            res = (res + dp[i][0] + dp[i][1]) % M;
        }
        printf("%I64d%c", res, k == 2 * n - 3 ? '\n' : ' ');
    }
}
int main(){
    cin >> n;
    a[0] = cnt[1] = 1;
    a[n] = 0;
    for(int i = 1; i < n; i++){
        cin >> a[i];
        cnt[i + 1] = cnt[i] * a[i] % M;
    }
    solve();
    return 0;
}