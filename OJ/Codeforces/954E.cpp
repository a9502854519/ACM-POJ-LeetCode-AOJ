#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MAX_N 200000 + 100

using namespace std;
typedef long long ll;

int n;
double T;
struct Data{
    double a, t;
    Data() {}
    Data(double a, double t) : a(a), t(t) {}
}p[MAX_N];

bool cmp(const Data& x, const Data& y){
    return x.t < y.t;
}
bool check(double k){
    double res = 0, v = k;
    bool ok = true;
    for(int i = 0; i < n && v > 0; i++){
        res += fmin(v, p[i].a) * p[i].t;
        v -= fmin(v, p[i].a);
    }
    if(res > T * k) return false;
    res = 0, v = k;
    for(int i = n - 1; i >= 0; i--){
        res += fmin(v, p[i].a) * p[i].t;
        v -= fmin(v, p[i].a);
    }
    return res >= T * k;
}
double solve(){
    sort(p, p + n, cmp);
    double ub = 0.0, lb = 0.0, mid;
    for(int i = 0; i < n; i++){
        ub += p[i].a;
    }
    if(T < p[0].t || T > p[n - 1].t) return 0.0;
    
    for(int i = 0; i < 100; i++){
        mid = (ub + lb) / 2;
        if(check(mid)) lb = mid;
        else ub = mid;
    }
    return lb;
}
int main(){
    cin >> n >> T;
    for(int i = 0; i < n; i++) scanf("%lf", &p[i].a);
    for(int i = 0; i < n; i++) scanf("%lf", &p[i].t);
    printf("%.8lf\n", solve());
    return 0;
}