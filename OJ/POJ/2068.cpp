#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_N 20
#define MAX_S (1<<13)

using namespace std;

int n, S;
int M[MAX_N];
int dp[MAX_S+1][MAX_N];

bool solve(){
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n; i++) dp[0][i] = true;
	for(int i = 1; i <= S; i++){
		for(int j = 0; j < n; j++){
			for(int k = 1; k <= min(i, M[j]); k++){
				dp[i][j] |= !dp[i-k][(j+1) % n];
			}
		}
	}
	return dp[S][0];
}

int main(){
	while(cin>>n){
		if(!n) break;
		n *= 2;
		cin>>S;
		memset(dp, -1, sizeof(dp));
		
		for(int i = 0; i < n; i++){
			cin>>M[i];
		}
		printf("%d\n", (int)solve());
	}
	return 0;
}