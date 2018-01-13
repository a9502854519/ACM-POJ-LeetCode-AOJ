#include<iostream>
#include<cstdio>
#define MAX_N 100
#define MAX_M 10

using namespace std;

int m, n;
int dp[MAX_M][MAX_N];
int s[MAX_M][MAX_N];

void solve(){
	for(int j = n - 2; j >= 0; j--){
		for(int i = 0; i < m; i++){
			int temp, chi;
			chi = i;
			temp = dp[chi][j+1];

			for(int k = -1; k <= 1; k++){
				int p = (i + k + m) % m;
				if(temp > dp[p][j+1]){
					temp = dp[p][j+1];
					chi = p;
				}else if(temp == dp[p][j+1] && p < chi){
					chi = p;
				}
			}
			dp[i][j] += temp;
			s[i][j] = chi;
		}
	}
	int res = 0;
	for(int i = 1; i < m; i++){
		if(dp[i][0] < dp[res][0]) res = i;
	}
	int u = res;
	for(int i = 0; i < n; i++){
		printf("%d%c", u+1, i == n - 1 ? '\n' : ' ');
		u = s[u][i];
	}
	printf("%d\n", dp[res][0]);
}
int main(){
	while(scanf("%d %d", &m, &n) != EOF){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &dp[i][j]);
			}

		}
		solve();
	}
	return 0;
}
