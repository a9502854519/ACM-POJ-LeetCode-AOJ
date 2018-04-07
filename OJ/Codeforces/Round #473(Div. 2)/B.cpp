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
#include<cstring>
#include<queue>
#include<unordered_map>
#define MAX_N 100000

using namespace std;
typedef long long ll;

int n, k, m;
string w[MAX_N];
ll a[MAX_N];
ll mn[MAX_N];
int group[MAX_N];
unordered_map<string, int> mp;

void solve(){
    memset(mn, 0x3f, sizeof(mn));
    for(int i = 0; i < k; i++){
        int x;
        cin >> x;
        for(int j = 0; j < x; j++){
            int y;
            cin >> y;
            y--;
            group[y] = i;
            mn[i] = min(mn[i], a[y]);
        }
    }
    ll sum = 0;
    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        int j = group[mp[s]];
        sum += mn[j];
    }
    cout << sum << endl;
}
int main(){
    cin >> n >> k >> m;
    for(int i = 0; i < n; i++){
        cin >> w[i];
        mp[w[i]] = i;
    }
    for(int i = 0; i < n; i++) cin >> a[i];
    solve();
    return 0;
}