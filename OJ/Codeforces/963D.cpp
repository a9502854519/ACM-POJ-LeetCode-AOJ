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
#include<bitset>
#define MAX_N 100000 + 10

using namespace std;

string s;
bitset<MAX_N> bs[26], tmp;

void init(){
    for(int i = 0; i < s.length(); i++){
        bs[s[i] - 'a'][i] = 1;
    }
}
void solve(){
    init();
    int q, k;
    string m;
    cin >> q;
    while(q--){
        cin >> k >> m;
        tmp = bs[m[0] - 'a'];
        vector<int> p;
        for(int i = 1; i < m.size(); i++){
            tmp &= bs[m[i] - 'a'] >> i;
        }
        for(int i = tmp._Find_first(); i < tmp.size(); i = tmp._Find_next(i)){
            p.push_back(i);
        }
        if(p.size() < k) printf("-1\n");
        else{
            int res = MAX_N + 10;
            for(int i = 0; i + k - 1 < p.size(); i++){
                res = min(res, p[i + k - 1] - p[i]);
            }
            printf("%d\n", res + m.size());
        }
    }
}
int main(){
    cin >> s;
    solve();
    return 0;
}