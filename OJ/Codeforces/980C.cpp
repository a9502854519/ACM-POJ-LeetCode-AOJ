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
#define MAX_N 100010

using namespace std;

int n, k;
int p[MAX_N], g[256];

void solve(){
    memset(g, -1, sizeof(g));
    for(int i = 0; i < n; i++){
        if(g[p[i]] == -1){
            int j = max(p[i] - k + 1, 0);
            while(g[j] != -1 && (j > 0 && g[j] == g[j - 1])) j++;
            fill(g + j, g + p[i] + 1, j);
        }
        printf("%d ", g[p[i]]);
    }
    cout << endl;
    // for(int i = 0; i < 15; i++) printf("%d ", g[i]);
    // cout << endl;
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++) scanf("%d", p + i);
    solve();
    return 0;
}