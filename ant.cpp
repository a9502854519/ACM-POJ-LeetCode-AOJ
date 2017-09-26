#include<iostream>
#include<algorithm>
#define M 1000000
using namespace std;
/*
dp[i][j] 前i個組成長度為j的集合個數
dp[i][j] = dp[i-1][j-k]  0<=k<=min(count[i],j);
*/

int main(){
	int T,A,S,B,a,*ant,*count,res;
	cin>>T>>A>>S>>B;
	int dp[T+1][A+1];
	ant = new int[A];
	count = new int[T+1];
	fill(count, count+T+1,0);
	for(int i=0;i<A;i++){
		cin>>a;
		count[a]++;
	}
	for(int i=0;i<=T;i++)
		fill(dp[i], dp[i]+A+1,0);
	dp[0][0] = 1;
	for(int i=1;i<=T;i++){
		dp[i][0] = 1;
		for(int j=1;j<=A;j++){
			for(int k=0;k<=j && k<=count[i];k++){
				dp[i][j] = (dp[i][j]%M + dp[i-1][j-k]%M)%M;
			}
		}
	}
	res = 0;
	for(int i=S;i<=B;i++)
		res+=dp[T][i];
	cout<<res%1000000<<endl;
	return 0;
}
	