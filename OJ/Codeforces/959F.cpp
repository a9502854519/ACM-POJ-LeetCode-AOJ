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
#define MAX_N 100000 + 100
#define INF 0x3f3f3f3f

using namespace std;
typedef long long ll;

const ll MOD = 1000000000 + 7;
int n, q;
int a[MAX_N], t[(1 << 20) + 10];
ll res[MAX_N];
vector<int> s;

void solve(){
    memset(t, 0x3f, sizeof(t));
    t[0] = 0;
    res[0] = 1;
    s.push_back(0);
    
    for(int i = 1; i <= n; i++){
        res[i] = res[i - 1];
        
        if(t[a[i]] < INF) res[i] = res[i] * 2 % MOD;
        else{
            int tmp = s.size();
            for(int j = 0; j < tmp; j++){
                t[s[j] ^ a[i]] = i;
                s.push_back(s[j] ^ a[i]);
            }
        }
    }
    int l, x;
    while(q--){
        scanf("%d %d\n", &l, &x);
        if(t[x] <= l) cout << res[l] << endl;
        else cout << "0\n";
    }
}
int main(){
    cin >> n >> q;
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    solve();
    return 0;
}