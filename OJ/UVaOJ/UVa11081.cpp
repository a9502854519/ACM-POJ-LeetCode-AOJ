#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX 60

using namespace std;

const int MOD = 10007;
int dp[MAX+1][MAX+1][MAX+1];
string a, b, c;

int solve(){
	memset(dp, 0, sizeof(dp));
	a = '$' + a;
	b = '$' + b;
	c = '$' + c;
	for(int i = 0; i < a.length(); i++){
		for(int j = 0; j < b.length(); j++){
			dp[i][j][0] = 1;
		}
	}
	for(int k = 1; k < c.length(); k++){
		for(int i = 0; i < a.length(); i++){
			for(int j = 0; j < b.length(); j++){
				if(i + j < k) continue;
				
				if(i > 0){ 
					dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k]) % MOD;
					if(c[k] == a[i]) dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1]) % MOD;
				}
				if(j > 0){
					dp[i][j][k] = (dp[i][j][k] + dp[i][j - 1][k]) % MOD;
					if(c[k] == b[j]) dp[i][j][k] = (dp[i][j][k] + dp[i][j - 1][k - 1]) % MOD;
				}
				if(i > 0 && j > 0){
					dp[i][j][k] = (dp[i][j][k] - ((a[i] == c[k]) + (b[j] == c[k])) * dp[i - 1][j - 1][k - 1] 
							- dp[i - 1][j - 1][k]) % MOD;
				}
				dp[i][j][k] = (dp[i][j][k] + MOD) % MOD;
			}
		}
	}
	return dp[a.length() - 1][b.length() - 1][c.length() - 1];
}
int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> a >> b >> c;
		cout << solve() << endl;
	}
	return 0;
}
