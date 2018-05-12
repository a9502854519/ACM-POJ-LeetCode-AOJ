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
#include<cstring>
#include<algorithm>

using namespace std;
typedef long long ll;

ll n, k, M, D;

void solve(){
    ll x = (n / M / k) + ((n / M) % k >= 1);
    ll res = x * M;
    x++;
    for(int cnt = 0; cnt < 10, x <= D; cnt++, x++){
        ll ub = M, lb = 0, mid;
        while(ub - lb > 1){
            mid = (ub + lb) / 2;
            if(n / mid / k + ((n / mid) % k >= 1) >= x) lb = mid;
            else ub = mid;
        }
        if(x <= D) res = max(res, lb * x);
    }
    cout << res << endl;
}
int main(){
    cin >> n >> k >> M >> D;
    solve();
    return 0;
}