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
#define MAX_N 100 + 10
#define INF 1E9

using namespace std;

int n;
char a[4][MAX_N][MAX_N];
int cnt[4][2];
//101....01   010.....10

void solve(){
    for(int k = 0; k < 4; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int tmp = (i + j) % 2;
                
                if(tmp == 0){
                    cnt[k][0] += a[k][i][j] == '0';
                    cnt[k][1] += a[k][i][j] == '1';
                }else{
                    cnt[k][0] += a[k][i][j] == '1';
                    cnt[k][1] += a[k][i][j] == '0';
                }
            }
        }
    }
    // for(int i = 0; i < 4; i++){
        // printf("cnt[%d][0] = %d  cnt[%d][1] = %d\n", i, cnt[i][0], i, cnt[i][1]);
    // }
    int res = INF;
    for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 4; j++){
            int tmp = cnt[i][0] + cnt[j][0];
            for(int k = 0; k < 4; k++){
                if(k != i && k != j) tmp += cnt[k][1];
            }
            res = min(res, tmp);
        }
    }
    cout << res << endl;
}
int main(){
    cin >> n;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < n; j++) scanf("%s", a[i][j]);
    }
    solve();
    return 0;
}