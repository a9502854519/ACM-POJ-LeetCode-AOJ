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
#define MAX_N 10000 + 100

using namespace std;
typedef long long ll;

ll X, d;
vector<ll> res;

void solve(){
    ll tmp = 1;
    while(X > 0){
        for(ll i = 1; i <= X; i <<= 1){
            res.push_back(tmp);
            X -= i;
        }
        tmp += d;
    }
    cout << res.size() << endl;
    for(int i = 0; i < res.size(); i++) printf("%I64d ", res[i]);
    cout << endl;
}
int main(){
    cin >> X >> d;
    solve();
    return 0;
}