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
#define MAX_N 100000 + 10

using namespace std;

int n, k;
int a[MAX_N];
int t[MAX_N];

void solve(){
    int res = 0;
    for(int i = 0; i < n; i++){
        if(t[i]) res += a[i];
    }
    int tmp = 0, sum = 0;
    for(int i = 0; i < k; i++){
        if(t[i] == 0) tmp += a[i];
    }
    for(int i = 0; i + k <= n; i++){
        sum = max(sum, tmp);
        if(i + k < n){
            if(t[i] == 0) tmp -= a[i];
            if(t[i + k] == 0) tmp += a[i + k];
        }
    }
    cout << res + sum << endl;
}
int main(){
    cin >> n >> k;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    for(int i = 0; i < n; i++) scanf("%d", t + i);
    solve();
    return 0;
}