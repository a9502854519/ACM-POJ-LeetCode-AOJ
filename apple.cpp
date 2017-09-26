#include<iostream>
#include<algorithm>

using namespace std;
/*
dp[i][j] : 第i分鐘，成本為j時的最大值
dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + !(Tree[i]^(j&1))
*/
int dp[31];
int Tree[1000];
int main(){
	int T,W,res;
	cin>>T>>W;
		for(int i=0;i<T;i++){
			cin>>Tree[i];
			Tree[i]--;
		}
		fill(dp,dp+31,0);
		dp[0] = 1 - Tree[0];
		dp[1] = Tree[0];
		
		for(int i=1;i<T;i++){
			dp[0] = dp[0] + 1 - Tree[i];
			for(int j=W;j>=1;j--){
				dp[j] = max(dp[j],dp[j-1]) + !(Tree[i]^(j&1));
			}
		}	
	
		res = 0;
		for(int i=0;i<=W;i++)
			res = max(res, dp[i]);
		cout<<res<<endl;
	
	return 0;
}	
		