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
typedef long long ll;

ll shift[70];
ll size[70];

void init(){
    for(int i = 0; i <= 60; i++){
        size[i] = 1LL << i;
    }
}
int get_height(ll X){
    int t = 0;
    while((1LL << t) <= X) t++;
    return t - 1;
}
ll add(ll v, ll a, ll m){
    return ((v + a) % m + m) % m;
}
void solve(){
    init();
    int q, t;
    ll X, K;
    cin >> q;
    while(q--){
        scanf("%d %I64d", &t, &X);
        int h = get_height(X);
        if(t < 3){
            scanf("%I64d", &K);
            for(int i = h; i <= (t == 1 ? h : 60); i++){
                K %= size[i];
                shift[i] = add(shift[i], K, size[i]);
                K <<= 1;
            }
        }else{
            X = add(X - (1LL << h), shift[h], size[h]);
            for(int i = h; i >= 0; i--){
                ll val = (1LL << i) + add(X, -shift[i], size[i]);
                printf("%I64d ", val);
                X >>= 1;
            }
            cout << endl;
        }
    }
}
int main(){
    solve();
    return 0;
}