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
#include<cmath>
#include<utility>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAX_N 200000 + 100

using namespace std;
typedef long long ll;

ll n, q, a[MAX_N], k[MAX_N], sum[MAX_N];

void solve(){
    for(int i = 1; i < n; i++) a[i] += a[i - 1];
    ll cnt = 0;
    for(int i = 0; i < q; i++){
        cnt += k[i];
        int j = lower_bound(a, a + n, cnt) - a;
        // printf("i = %d  j = %d  cnt = %d\n", i, j, cnt);
        if(cnt >= a[n - 1]) cnt = 0;
        printf("%I64d\n", cnt ? n - j - (a[j] == cnt) : n);
    }
}
int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++) scanf("%I64d", a + i);
    for(int i = 0; i < q; i++) scanf("%I64d", k + i);
    solve();
    return 0;
}