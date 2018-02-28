#include<iostream>
#include<cstdio>
#define EPS 1E-6

using namespace std;

int n, m;

int main(){
    cin >> n >> m;
    double res = 1e20;
    for(int i = 0; i < n; i++){
        double a, b;
        cin >> a >> b;
        if(a / b < res) res = a / b;
    }
    printf("%.9lf\n", m * res);
    return 0;
}