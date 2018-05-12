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

using namespace std;
typedef long long ll;

ll a[14];

void solve(){
    ll res = 0;
    for(int i = 0; i < 14; i++){
        if(a[i] > 0){
            ll cnt = 0;
            for(int j = 1; j < 14; j++){
                int k = (i + j) % 14;
                ll tmp = a[k] + a[i] / 14 + (a[i] % 14 >= j);
                if(tmp % 2 == 0) cnt += tmp;
            }
            if(a[i] / 14 % 2 == 0) cnt += a[i] / 14;
            res = max(res, cnt);
        }
    }
    cout << res << endl;
}
int main(){
    for(int i = 0; i < 14; i++) scanf("%d", a + i);
    solve();
    return 0;
}