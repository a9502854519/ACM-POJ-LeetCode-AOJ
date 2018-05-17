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

using namespace std;

int n;
string s[3];
int frq[52];
char winner[][6] = {"Kuro", "Shiro", "Katie", "Draw"};

void solve(){
    int res = 0, win = -1;
    for(int i = 0; i < 3; i++){
        memset(frq, 0, sizeof(frq));
        for(char c : s[i]){
            int idx = c <= 'Z' ? c - 'A' : c - 'a' + 26;
            frq[idx]++;
        }
        int mx = -1;
        for(int j : frq){
            if(j > 0){
                int cnt;
                if(j < s[i].length()) cnt = min(j + n, int(s[i].length()));
                else cnt = j - (n == 1);
                mx = max(mx, cnt);
            }
        }
        if(res < mx){
            res = mx;
            win = i;
        }else if(res == mx){
            win = 3;
        }
    }
    cout << winner[win] << endl;
    
}
int main(){
    cin >> n >> s[0] >> s[1] >> s[2];
    solve();
    return 0;
}