/*
dp[i][j] : 前i個topic，使用j個lecture，所得的最小DI
dp[i+k][j+1] = dp[i][j] + (L - sum(i+1 ~ i+k) - 10)^2 or -C 										  

*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#define INF 1.0E8

using namespace std;
int get(int s, int C){
	if(s == 0)
		return 0;
	if(s >=1 && s <= 10)
		return  -C;
	return (s-10)*(s-10);
}
int t[1001];
int dp[1001][1001];
int main(){
	int n,L,C,T,sum,m;
	for(int ct = 1;;ct++){
		cin>>n;
		if(n == 0) break;
		if(ct > 1) printf("\n");
		cin>>L>>C;
		for(int i=0;i<=n;i++){
			if(i<n) cin>>t[i+1];
			fill(dp[i],dp[i]+n+1,INF);
		}
		dp[0][0] = 0;
		for(int j=0;j<n;j++){ //lecture
			for(int i=0;i<n;i++){	//topic
				if(dp[i][j] < INF){
					sum = 0;
					for(int k=1;i+k<=n;k++){
						sum+=t[i+k];
						if(sum > L) break;
						m = get(L-sum,C);
						dp[i+k][j+1] = min(dp[i+k][j+1], dp[i][j] + m);
					}
				}
			}
			if(dp[n][j+1] < INF){
				printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n",ct,j+1,dp[n][j+1]);
				break;
			}
		}
	}
	return 0;
}	
					
		
		
	