#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_N 100
#define INF 1E9

using namespace std;

int  dp[MAX_N][2 * MAX_N - 1];
int  rdp[MAX_N][2 * MAX_N - 1];
int n;

int solve(){
	
	for(int i = 0; i < n - 1; i++){
		for(int j = i; j < 2*n-i-1; j += 2){
			int m = INF;
			if(j + 2 < 2*n-i-1 && dp[i][j+1] > 0){
				for(int k = 0; k < 3; k += 2){
					m = min(dp[i][j+k], m);
				}
				if(m > 0 && dp[i+1][j+1] > 0) dp[i+1][j+1] = m+2;
			}
		}
	}

	for(int i = n - 3; i > 0; i--){
		for(int j = i + 1; j < 2*n-i-2; j += 2){
			int m = INF;
			if(j + 2 <  2*n-i-2 && rdp[i][j+1] > 0){
				for(int k = 0; k < 3; k += 2){
					m = min(rdp[i][j+k], m);
				}
				if(m > 0 && rdp[i-1][j+1] > 0) rdp[i-1][j+1] = m+2;
			}
		}
	}
	int res = 0;
	for(int i = 0; i < n; i++){
		for(int j = i; j < 2*n-i-1; j++){
			if(((j - i) & 1)) res = max(res, rdp[i][j]);
			else              res = max(res,  dp[i][j]);
		}
	}

/*	for(int i = 0;  i < n; i++){
		for(int j = 0; j < 2 * n - 1; j++){
			if(j < i || j >= i+2*(n-i)-1) printf(" ");
			else printf("%d", rdp[i][j]);
		}
		printf("\n");
	}
*/	return (res+1)*(res+1)/4;
}
		       	
int main(){
	int c = 1;
	while(cin>>n){
		if(!n) break;
		memset(dp, 0, sizeof(dp));
		memset(rdp, 0, sizeof(rdp));
		for(int i = 0; i < n; i++){
			char str[2*n];
			scanf("%s", str);
			for(int j = 0; str[j] != '\0'; j++){
				if(str[j] == '-'){
					dp[i][j+i] = 1;
					rdp[i][j+i] = 1;
				}
			
			}
		}
		printf("Triangle #%d\nThe largest triangle area is %d.\n\n", c++, solve());
	}
	return 0;
}

