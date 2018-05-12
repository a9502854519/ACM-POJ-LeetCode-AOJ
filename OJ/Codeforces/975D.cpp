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
#include<cmath>
#define MAX_N 200000 + 100

using namespace std;

double EPS = 1e-7;
double add(double a, double b){
    if(fabs(a + b) < EPS * (fabs(a) + fabs(b))) return 0;
    return a + b;
}
bool equal(double a, double b){
    return fabs(a - b) < EPS;
    // return add(a, -b) == 0;
}
struct P{
    double x, y;
    int x1, y1;//copy
    P() {}
    P(double x, double  y) : x(x), y(y) {
        x1 = (int)x;
        y1 = (int)y;
    }
    
    void copy(){
        x1 = (int)x;
        y1 = (int)y;
    }
    bool operator < (const P& p) const{
        if(!equal(y, p.y)) return y < p.y;
        else return x < p.x;
    }
    P operator + (const P& p) const{
        return P(add(x, p.x), add(y, p.y));
    }
    P operator - (const P& p) const{
        return P(add(x, - p.x), add(y, - p.y));
    }
    double dot(const P& p) const{
        return add(x * p.x, y * p.y);
    }
    double det(const P& p) const{
        return add(x * p.y, -y * p.x);
    }
};

int n;
double a, b;
P p[MAX_N];

void solve(){
    double theta = atan(a);
    for(int i = 0; i < n; i++){
        double x = p[i].x, y = p[i].y;
        double s = sin(theta), c = cos(theta);
        p[i].x = add(c * x, s * y);
        p[i].y = add(-s * x,  c * y);
    }
    sort(p, p + n);
    
    long long res = 0;
    long long  sum = 0, cnt = 1;
    for(int i = 1; i < n; i++){
        if(p[i].y1 == p[i - 1].y1 && p[i].x1 == p[i - 1].x1) cnt++;
        else{
            res += sum * cnt * 2;
            sum = ((p[i].x1 - p[i - 1].x1) * a == (p[i].y1 - p[i - 1].y1) ? sum + cnt : 0);
            cnt = 1;
        }
    }
    res += sum * cnt * 2;
    cout << res << endl;
}
int main(){
    cin >> n >> a >> b;
    for(int i = 0; i < n; i++){
        scanf("%*d %lf %lf\n", &p[i].x, &p[i].y);
        p[i].copy();
    }
    solve();
    return 0;
}