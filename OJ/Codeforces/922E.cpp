#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define MAX_N 1000 + 100
#define MAX_C 10000 + 10

using namespace std;
typedef long long ll;

ll n, W, B, X;
ll c[MAX_N], cost[MAX_N];
ll dp[MAX_C];

int solve(){
    int res = c[1];
    for(int i = 0; i <= c[1]; i++){
        if(W - i * cost[1] >= 0){
            dp[i] = W - i * cost[1];
            res = i;
        }
    }
    
    for(int i = 1; i < n; i++){
        for(int j = res; j >= 0; j--){
            for(int m = c[i + 1]; m >= 0; m--){
                if(min(dp[j] + X, W + B * j) >= cost[i + 1] * m){
                    ll tmp = min(dp[j] + X, W + B * j) - cost[i + 1] * m;
                    dp[j + m] = max(dp[j + m], tmp);
                    res = max(res, j + m);
                }
            }
        }
    }
    return res;
}
int main(){
    cin >> n >> W >> B >> X;
    for(int i = 1; i <= n; i++) scanf("%I64d", c + i);
    for(int i = 1; i <= n; i++) scanf("%I64d", cost + i);
    
    cout << solve() << endl;
    return 0;
}