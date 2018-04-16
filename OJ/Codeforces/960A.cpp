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

using namespace std;

string S;
int cnt[3];

bool solve(){
    for(int i = 0, k = 0; i < S.length(); i++){
        if(S[i] - 'a' < k) return false;
        if(S[i] - 'a' > k) k = S[i] - 'a';
        cnt[k]++;
    }
    return cnt[0] > 0 && cnt[1] > 0 && (cnt[2] == cnt[0] || cnt[2] == cnt[1]);
}
int main(){
    cin >> S;
    printf("%s\n", solve() ? "YES" : "NO");
    return 0;
}