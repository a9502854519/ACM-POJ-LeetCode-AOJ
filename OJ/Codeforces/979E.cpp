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
#define MAX_N 51
// #define TIME

using namespace std;
typedef long long ll;

int n, p, c[MAX_N];
ll dp[MAX_N][MAX_N][MAX_N], t[MAX_N];
const ll M = 1E9 + 7;

void init(){
    t[0] = 1;
    for(int i = 1; i <= n; i++) t[i] = t[i - 1] * 2 % M;
}
inline ll add(ll a, ll b){
    return (a + b) % M;
}
void solve(){
    init();    
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int ob = 0; ob <= i; ob++){
            for(int ow = 0; ow + ob <= i; ow++){
                if(c[i] == 0 || c[i] == -1){ // black
                    //odd black
                    if(ob - 1 >= 0){
                        dp[i][ob][ow] = add(dp[i][ob][ow], dp[i - 1][ob - 1][ow] * t[ow - 1 >= 0 ? ow - 1 : 0] % M * t[i - 1 - ow] % M);
                    }
                    //even black
                    if(ow >= 1){
                        dp[i][ob][ow] = add(dp[i][ob][ow], dp[i - 1][ob][ow] * t[ow - 1] % M * t[i - 1 - ow] % M);
                    }
                }
                if(c[i] == 1 || c[i] == -1){ // while
                    //odd white
                    if(ow - 1 >= 0){
                        dp[i][ob][ow] = add(dp[i][ob][ow], dp[i - 1][ob][ow - 1] * t[ob - 1 >= 0 ? ob - 1 : 0] % M * t[i - 1 - ob] % M);
                    }
                    //even white
                    if(ob >= 1){
                        dp[i][ob][ow] = add(dp[i][ob][ow], dp[i - 1][ob][ow] * t[ob - 1] % M * t[i - 1 - ob] % M);
                    }
                }
            }
        }
    }
    ll res = 0;
    for(int ob = 0; ob <= n; ob++){
        for(int ow = 0; ob + ow <= n; ow++){
            if((ob + ow) % 2 == p){
                res = add(res, dp[n][ob][ow]);
            }
        }
    }
    
    cout << res << endl;
}
int main(){
#ifdef TIME
    clock_t S = clock();
#endif
    cin >> n >> p;
    for(int i = 1; i <= n; i++) scanf("%d", c + i);
    solve();
#ifdef TIME
    printf("Running time : %.3lf\n", double(clock() - S) / CLOCKS_PER_SEC);
#endif
    return 0;    
}