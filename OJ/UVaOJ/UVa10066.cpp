#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 100

using namespace std;

int N1, N2;
int c1[MAX_N+1], c2[MAX_N+1];
int dp[MAX_N+1][MAX_N+1];

int solve(){
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 0;

	for(int i = 1; i <= N1; i++){
		for(int j = 1; j <= N2; j++){
			if(c1[i] == c2[j]){
				dp[i][j] = dp[i-1][j-1] + 1;
			}else{
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
	return dp[N1][N2];
}

int  main(){
	int t = 1;
	while(true){
		scanf("%d %d", &N1, &N2);
		if(!N1 && !N2) break;

		for(int i = 1; i <= N1; i++) scanf("%d", c1+i);
		for(int i = 1; i <= N2; i++) scanf("%d", c2+i);
		printf("Twin Towers #%d\nNumber of Tiles : %d\n\n", t++, solve());
	}
	return 0;
}	

