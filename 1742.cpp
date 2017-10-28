/* 有個數限制的背包問題*/
#include<iostream>
#include<cstring>
#include<vector>
#define MAX_N 100
#define MAX_M 100000

using namespace std;


int A[MAX_N];
int C[MAX_N];
int dp[MAX_M+1];

void solve(){
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= m; j++){
			if(dp[j] >= 0)                       dp[j] = C[i];
			else if(j < A[i] || dp[j-A[i]] <= 0) dp[j] = -1;
			else                                 dp[j] = dp[j-A[i]] - 1;
		}
	}
	res = 0;
	for(int i = 1; i <= m; i++){
		if(dp[i] >= 0) res++;
	}
	cout<<res<<endl;
}

int main(){
	int n,m,res;
	while(cin>>n>>m){
		if(n == 0 && m == 0) break;
		for(int i = 0; i < n; i++){
			cin>>A[i];
		}
		for(int i = 0; i < n; i++){
			cin>>C[i];
		}
		solve();
	}

	return 0;
}
