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
#define MAX_W 100000 + 10

using namespace std;

int w, l;
int a[MAX_W];

void solve(){
    int res = 0, cap;
    for(int i = 0; i < l; i++) res += a[i];
    cap = res;
    for(int i = l; i < w - 1; i++){
        cap += a[i] - a[i - l];
        res = min(res, cap);
    }
    cout << res << endl;
}
int main(){
    cin >> w >> l;
    for(int i = 0; i < w - 1; i++) scanf("%d", a + i);
    solve();
    return 0;
}