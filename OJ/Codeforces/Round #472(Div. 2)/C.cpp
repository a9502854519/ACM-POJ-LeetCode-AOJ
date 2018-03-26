#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MAX_N 100000

using namespace std;

int n, U;
double E[MAX_N];

void solve(){
    double res = -1e9;
    for(int i = 0; i < n; i++){
        int k = upper_bound(E, E + n, E[i] + U) - E - 1;
        if(k > i + 1){
            double tmp = (E[k] - E[i + 1]) / (E[k] - E[i]);
            res = max(res, tmp);
        }
    }
    if(res < 0) cout << "-1\n";
    else printf("%.10f\n", res);
}
int main(){
    cin >> n >> U;
    for(int i = 0; i < n; i++) cin >> E[i];
    solve();
    return 0;
}