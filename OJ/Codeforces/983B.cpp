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
#define MAX_N 5010

using namespace std;

int n, q, l, r;
int f[MAX_N][MAX_N], res[MAX_N][MAX_N];

void solve(){
    for(int k = 1; k < n; k++){
        for(int i = 0; i + k < n; i++){
            int j = i + k;
            f[i][j] = f[i][j - 1] ^ f[i + 1][j];
            res[i][j] = max(max(res[i][j - 1], res[i + 1][j]), f[i][j]);
            // printf("f[%d][%d] = %2d(%2d ^ %2d)  res = %2d\n", i, j, f[i][j], f[i][j - 1], f[i + 1][j], res[i][j]);
        }
    }
    cin >> q;
    while(q--){
        scanf("%d %d\n", &l, &r);
        printf("%d\n", res[l - 1][r - 1]);
    }
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &f[i][i]);
        res[i][i] = f[i][i];
    }
    solve();
    return 0;
}