#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int hh, mm;
int H, D, N;
double C;

int myceil(int a, int b){
    return a / b + (a % b > 0);
}

void solve(){
    double res = myceil(H, N) * C;
    if(hh >= 20) res *= 0.8;
    else{
        int gap = (20 - hh) * 60 - mm;
        res = min(res, myceil((H + D * gap), N) * C * 0.8);
    }
    printf("%.4f\n", res);
}
int main(){
    cin >> hh >> mm;
    cin >> H >> D >> C >> N;
    solve();
    return 0;
}