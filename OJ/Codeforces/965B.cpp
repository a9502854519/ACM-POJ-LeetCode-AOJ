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
#define MAX_N 100 + 10

using namespace std;

int n, k;
char f[MAX_N][MAX_N];
int cnt[MAX_N][MAX_N];

void calc(int i, int j){
    bool ok = (j + k - 1) < n;
    for(int c = 0; c < k; c++){
        ok &= f[i][j + c] == '.';
    }
    if(ok) for(int c = 0; c < k; c++) cnt[i][j + c]++;
    ok = (i + k - 1) < n;
    for(int c = 0; c < k; c++){
        ok &= f[i + c][j] == '.';
    }
    if(ok) for(int c = 0; c < k; c++) cnt[i + c][j]++;
}
void solve(){
    int x = 0, y = 0, res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(f[i][j] == '.'){
                calc(i, j);
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(cnt[i][j] > res){
                res = cnt[i][j];
                x = i, y = j;
            }
        }
    }
    printf("%d %d\n", x + 1, y + 1);
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        scanf("%s", f + i);
    }
    solve();
    return 0;
}