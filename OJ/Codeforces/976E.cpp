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
#include<algorithm>
#include<utility>
#define MAX_N 200100

using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;

ll n, a, b;
P v[MAX_N];

bool cmp(const P& x, const P& y){
    return x.first - x.second > y.first - y.second;
}
void solve(){
    sort(v, v + n, cmp);
    ll res = 0, sum = 0;
    for(int i = 0; i < n; i++) sum += (i < b && v[i].first > v[i].second ? v[i].first : v[i].second);
    res = sum;
    if(b > 0){
        for(int i = 0; i < n; i++){
            if(i < b) res = max(res, sum - max(v[i].first, v[i].second) + (v[i].first << a));
            else res = max(res, sum - v[i].second - max(v[b - 1].first, v[b - 1].second) + v[b - 1].second + (v[i].first << a));
        }
    }
    cout << res << endl;
}
int main(){
    cin >> n >> a >> b;
    for(int i = 0; i < n; i++){
        scanf("%I64d %I64d\n", &v[i].first, &v[i].second);
    }
    solve();
    return 0;
}