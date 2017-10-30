/* 有個數限制的背包問題 */

#include<iostream>
#include<algorithm>
#include<cstring>
#define MAX_T 1000
#define MAX_A 1000
#define M 1000000

using namespace std;

int dp[MAX_T+1][MAX_A+1];
int T, A, S, B;
int ct[MAX_T+1];

void solve(){
	dp[0][0] = 1;
	for(int i = 1; i <= T; i++){
		dp[i][0] = 1;
		for(int j = 1; j <= A; j++){
			if(j - 1 - ct[i] >= 0){
				dp[i][j] = (dp[i-1][j] % M + dp[i][j-1] % M - dp[i-1][j-1-ct[i]] % M + M) % M;
			}else{
				dp[i][j] = (dp[i-1][j] % M + dp[i][j-1] % M) % M;
			}
		}
	}
	int res = 0;
	for(int i=S;i<=B;i++) res += dp[T][i];
	cout<<res%1000000<<endl;
}

int main(){
	cin>>T>>A>>S>>B;
	
	memset(ct, 0, sizeof(ct));
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < A; i++){
		int a;
		cin>>a;
		ct[a]++;
	}
	solve();
	
	return 0;
}
