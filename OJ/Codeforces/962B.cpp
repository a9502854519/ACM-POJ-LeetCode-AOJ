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
#define MAX_N 200000 + 10

using namespace std;

int n, a, b;
char seat[MAX_N];

void swap(int &a, int &b){
    b ^= a;
    a ^= b;
    b ^= a;
}
void solve(){
    int res = 0;
    for(int i = 0; i < n && (a > 0 || b > 0);){
        if(a > b) swap(a, b);
        bool k = 0;
        while(i < n && seat[i++] == '.'){
            if((k == 0 && b == 0) || (k == 1 && a == 0)) break;
            k ? a-- : b--;
            res++;
            k = 1 - k;
        }
    }
    cout << res << endl;
}
int main(){
    cin >> n >> a >> b;
    scanf("%s", seat);
    solve();
    return 0;
}