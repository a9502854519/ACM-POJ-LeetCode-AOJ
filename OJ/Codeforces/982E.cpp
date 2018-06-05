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
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, m, px, py, vx, vy;

ll extgcd(ll a, ll b, ll& x, ll& y){
    ll d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else{
        x = 1, y = 0;
    }
    return d;
}
void solve(){
    if(vx != 0 && vy != 0){
        ll k, gcd, x, y, gx, gy;    //nx + my = k
        gx = vx < 0 ? n - px : px;
        gy = vy < 0 ? m - py : py;
        gcd = extgcd(n, m, x, y);
        k = gx - gy;
        if(k % gcd != 0){
            printf("-1\n");
        }else{
            x = x * abs(k) / gcd % (m / gcd);
            y = y * abs(k) / gcd % (n / gcd);
            if(k > 0){
                if(x < 0) x += m / gcd;
                if(y > 0) y = n / gcd - y;
            }else{
                if(x > 0) x = m / gcd - x;
                if(y < 0) y += n / gcd;
            }
            if(x == 0) x += m / gcd;
            if(y == 0) y += n / gcd;
            printf("%I64d %I64d\n", (x + (vx < 0)) % 2 == 0 ? 0 : n, (y + (vy < 0)) % 2 == 0 ? 0 : m);
        }
    }else{
        if(vx != 0){
            if(py != 0 && py != m) printf("-1\n");
            else printf("%I64d %I64d\n", vx > 0 ? m : 0, py);
        }else{
            if(px != 0 && px != n) printf("-1\n");
            else printf("%I64d %I64d\n", px, vy > 0 ? n : 0);
        }
    }

}
int main(){
#ifdef TIME
    clock_t S = clock();
#endif
    cin >> n >> m >> px >> py >> vx >> vy;
    solve();
#ifdef TIME
    printf("Running time : %.3lf\n", double(clock() - S) / CLOCKS_PER_SEC);
#endif
    return 0;    
}