#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define INF 1E13
using namespace std;

int MAX_INT32 = (1<<31)-1;
long long int dp[200][200];

long long int solve(int i,int j){
	long long int res = 0;
	long long int temp;
	if(dp[i][j] < INF){
		return dp[i][j];
	}
	
	if(j < i)
		return 0;
	
	for(int k = i,ct = 0;ct<10; k++,ct++){
		if(k+9<=j && dp[k][k+9] < INF){
			temp = solve(i, k-1) + dp[k][k+9] + solve(k+10, j);
			if(res < temp) res = temp;
		}else if(k+8<=j && dp[k][k+8] < INF){
			temp = solve(i, k-1) + dp[k][k+8] + solve(k+9, j);
			if(res < temp) res = temp;
		}
	}
	dp[i][j] = res;
	return dp[i][j];
}
	
int main(){
	string s;
	long long int temp;
	int N,n;
	cin>>N;
	for(int ct=0;ct<N;ct++){
		s.clear();
		cin>>s;
		n = s.size();
		for(int i=0;i<n;i++){
			fill(dp[i],dp[i]+n,INF);
			dp[i][i] = (long long int)(s[i]-'0');
		}
		
		for(int i=0;i<n-1;i++){
			for(int j=i+1;j<n;j++){
				temp = dp[i][j-1]*10+dp[j][j];
				if(temp <= MAX_INT32){
					dp[i][j] = temp;
				}
			}
		}
		cout<<solve(0,n-1)<<endl;
	}
	return 0;
}