#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 500 + 10

using namespace std;
typedef long long ll;

const ll MOD = 1E9 + 7;
int m[MAX_N][MAX_N];
ll dp[2][MAX_N][MAX_N];
int n;

ll solve(){
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < n; i++){
        dp[0][i][i + 1] = dp[1][i][i + 1] = 1;
    }
    for(int k = 2; k <= n; k++){
        for(int i = 0; i + k <= n; i++){
            int j = i + k;
            for(int x = i + 1; x < j; x++){
                if(m[i][x]){
                    dp[0][i][j] = (dp[0][i][j] + (dp[0][i][x] * dp[0][x][j]) % MOD) % MOD;
                }
                if(m[x][j]){
                    dp[1][i][j] = (dp[1][i][j] + (dp[1][i][x] * dp[0][x][j]) % MOD) % MOD;
                }
            }
            dp[0][i][j] = (dp[0][i][j] + dp[1][i][j]) % MOD;
        }
    }
    return dp[1][0][n];
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &m[i][j]);
        }
    }
    for(int i = 1; i < n; i++){
        m[i][n] = m[i][0];
        m[n][i] = m[0][i];
    }
    m[0][n] = m[n][0] = 1;
    cout << solve() << endl;
    return 0;
}