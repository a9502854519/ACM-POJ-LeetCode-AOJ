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
#define MAX_N 200000 + 100
#define INF 2E9

using namespace std;
typedef long long ll;

int n;
int x[MAX_N];
char c[MAX_N];

void solve(){
    ll res = 0;
    for(int i = 0, r = -INF, b = -INF, p = -INF, mr = 0, mb = 0; i < n; i++){
        if(c[i] != 'B'){// R or P
            if(r != -INF){
                res += x[i] - r;
                mr = max(mr, x[i] - r);
            }
            r = x[i];
        }
        if(c[i] != 'R'){ // B or P
            if(b != -INF){
                res += x[i] - b;
                mb = max(mb, x[i] - b);
            }
            b = x[i];
        }
        if(c[i] == 'P'){
            if(p != -INF) res += min(x[i] - p - mr - mb, 0);
            p = x[i];
            mr = mb = 0;
        }
    }
    cout << res << endl;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d %c", x + i, c + i);
    }
    solve();
    return 0;
}