#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


/*
dp[i][j]  利用前i個硬幣完成j時剩下的i的個數
dp[i][j] = Ci                if dp[i-1][j] >=0            -->代表前i-1個就能完成j
         = -1                if(j<Ai || dp[i-1][j-Ai]<=0  -->代表Ai太大無法完成j，或是前i-1個無法完成j
         = dp[i-1][j-Ai] - 1 otherwise		   
*/
int A[100];
int C[100];
int dp[100001];
int main(){
	int n,m,res;
	while(cin>>n>>m){
		if(n==0 && m==0) break;
		for(int i=0;i<n;i++)
			cin>>A[i];
		for(int i=0;i<n;i++)
			cin>>C[i];
		
		fill(dp,dp+m+1,-1);
		dp[0] = 0;
		for(int i=0; i<n;i++){
			for(int j=0;j<=m;j++){
				if(dp[j]>=0)
					dp[j] = C[i];
				else if(j<A[i] || dp[j-A[i]] <=0)
					dp[j] = -1;
				else
					dp[j] = dp[j-A[i]] - 1;
				//cout<<"dp["<<i+1<<"]["<<j<<"]="<<dp[j]<<endl;
			}
		}
		res = 0;
		for(int i=1;i<=m;i++){
			if(dp[i]>=0) res++;
		}
		cout<<res<<endl;
	}

	return 0;
}
