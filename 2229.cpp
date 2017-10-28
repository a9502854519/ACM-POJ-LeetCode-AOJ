#include<iostream>
/* 沒有個數限制的背包問題 */
/* 這題用C++提交可能會超時
 * 請改用G++
 */



#include<cstring>
#define MAX_N 1000000

using namespace std;

const int mod = 1000000000;

int N;
int dp[MAX_N + 1];

void solve(){
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for(int k = 1; k <= N; k *= 2){
		for(int i = k; i <= N; i++){
			dp[i] = (dp[i] + dp[i-k] % mod) % mod;
		}
	}
	cout<<dp[N]<<endl;
}
int main(){
	cin>>N;
	solve();
	return 0;
}