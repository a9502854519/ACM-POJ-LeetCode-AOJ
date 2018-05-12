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
#define MAX_N 300 + 10

using namespace std;

int n, d[MAX_N], v[1000 + 10];

void solve(){
    vector<pair<int, int> > res;
    for(int i = 0, idx = 0; i <= n / 2; i++){
        for(int j = 0; j < d[i] - (i > 0 ? d[i - 1] : 0); j++, idx++){
            for(int k = 1; k <= d[n - 1 - i] - v[idx]; k++){
                res.push_back(make_pair(idx + 1, k + idx + 1));
                v[k + idx]++;
            }
            v[idx] = d[n - 1 - i];
        }
    }
    printf("%d\n", res.size());
    for(int i = 0; i < res.size(); i++) printf("%d %d\n", res[i].first, res[i].second);
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", d + i);
    solve();
    return 0;
}