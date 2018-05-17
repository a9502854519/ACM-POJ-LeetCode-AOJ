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
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX_N 5010

using namespace std;

string s;
vector<int> p[26];
int cnt[26];

void solve(){
    int n = s.length();
    double res = 0.0;

    for(int i = 0; i < n; i++){
        p[s[i] - 'a'].push_back(i);
    }
    for(int i = 0; i < 26; i++){
        double mx = 0.0;
        for(int j = 1; j < n; j++){
            double a = 0.0, b = 0.0;
            memset(cnt, 0, sizeof(cnt));
            for(int k : p[i]){
                cnt[s[(k + j) % n] - 'a']++;
            }
            for(int i = 0; i < 26; i++){
                b += cnt[i];
                a += cnt[i] == 1;
            }
            mx = max(mx, a / b);
        }
         
        res += mx * double(p[i].size()) / double(n);
    }
    printf("%.7lf\n", res);
}
int main(){
    cin >> s;
    solve();
    return 0;
}