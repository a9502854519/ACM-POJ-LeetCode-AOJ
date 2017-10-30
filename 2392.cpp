/*　有個數限制的背包問題　
 *　 把高度限制比較小的放
 *  在下面
 */
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAX_K 400
#define MAX_A 40000

using namespace std;

struct Block{
	int limit, height, number;
}A[MAX_K+1];
int dp[MAX_A+1];
int K;	 

bool cmp(const Block& a, const Block& b){
	return a.limit < b.limit;
}
void solve(){
	sort(A+1, A+1+K, cmp);
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	int ans = 0;
	A[0].limit = 0;

	for(int i = 1; i <= K; i++){
		for(int j = 0; j <= A[i].limit; j++){
			if(dp[j] >= 0){
				dp[j] = A[i].number;
			}else if(j < A[i].height || dp[j-A[i].height] <= 0){
				dp[j] = -1;
			}else{
				dp[j] = dp[j-A[i].height] - 1;
			}
			if(dp[j] >= 0) ans = max(ans, j);
		}
	}
	cout<<ans<<endl;
}
int main(){
	cin>>K;
	for(int i = 1; i <= K; i++){
		cin>>A[i].height>>A[i].limit>>A[i].number;
	}
	solve();
	return 0;
}
