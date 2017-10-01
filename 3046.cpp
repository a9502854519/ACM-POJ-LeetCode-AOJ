#include<iostream>
#include<algorithm>
#define M 1000000

using namespace std;

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
	for(int i=0;i<=T;i++){
		fill(dp[i], dp[i]+A+1,0);
	}
	dp[0][0] = 1;
	for(int i = 1; i <= T; i++){
		dp[i][0] = 1;
		for(int j = 1; j <= A; j++){
			if(j - 1 - count[i] >= 0){
				dp[i][j] = (dp[i-1][j] % M + dp[i][j-1] % M - dp[i-1][j-1-count[i]] % M + M) % M;
			}else{
				dp[i][j] = (dp[i-1][j] % M + dp[i][j-1] % M) % M;
			}
		}
	}
	res = 0;
	for(int i=S;i<=B;i++)
		res+=dp[T][i];
	cout<<res%1000000<<endl;
	return 0;
}
	