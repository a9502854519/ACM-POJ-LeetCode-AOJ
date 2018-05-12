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
#define MAX_N 10010

using namespace std;

double EPS = 1e-10;
double add(double a, double b){
    if(fabs(a + b) < EPS * (fabs(a) + fabs(b))) return 0;
    return a + b;
}
struct P{
    double x, y;
    P() {}
    P(double x, double  y) : x(x), y(y) {}
    
    P operator + (const P& p) const{
        return P(add(x, p.x), add(y, p.y));
    }
    P operator - (const P& p) const{
        return P(add(x, - p.x), add(y, - p.y));
    }
    P operator * (double d) const{
        return P(x * d, y * d);
    }
    double dot(const P& p) const{
        return add(x * p.x, y * p.y);
    }
    double det(const P& p) const{
        return add(x * p.y, -y * p.x);
    }
    double dis() const{
        return sqrt(add(x * x, y * y));
    }
};

int n, q;
P p[MAX_N], c(0, 0);
P vec[MAX_N];

P pos(int i, int j){
    double coss = vec[i].dot(vec[j]) / vec[i].dis() / vec[j].dis(),
           sinn = vec[i].det(vec[j]) / vec[i].dis() / vec[j].dis();
    return c + P(-sinn, coss) * vec[j].dis();
}
void calc_centroid(){
    double A = 0.0;
    p[n] = p[0];
    for(int i = 0; i < n; i++){
        A = add(A, p[i].det(p[i + 1]));
        c = c + (p[i] + p[i + 1]) * p[i].det(p[i + 1]);
    }
    c.x /= 3 * A;
    c.y /= 3 * A;
}
void solve(){
    P zp = p[0];
    for(int i = 0; i < n; i++) p[i] = p[i] - zp;
    
    calc_centroid();
    for(int i = 0; i < n; i++){
        vec[i] = p[i] - c;
    }
    
    int f, t, v, pin1 = 0, pin2 = 1;
    for(int i = 1, move = 0; i <= q; i++){
        scanf("%d", &t);
        if(t == 1){
            scanf("%d %d", &f, &t);
            f--; t--;
            int idx = f == pin1 ? pin2 : pin1; //旋轉中心
            P target = move == 0 ? p[idx] : pos(pin1, idx);
            c = target - P(0, vec[idx].dis());
            pin1 = idx;
            pin2 = t;
            move = 1;
        }else{
            scanf("%d", &v);
            v--;
            P res = move == 0 ? p[v] : pos(pin1, v);
            printf("%.10lf %.10lf\n", res.x + zp.x, res.y + zp.y);
        }
    }
}
int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++) scanf("%lf %lf\n", &p[i].x, &p[i].y);
    solve();
    return 0;
}